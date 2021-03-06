-- Render a textfile.
-- @module textfile
-- @author Eduardo Tongson <propolice@gmail.com>
-- @license MIT <http://opensource.org/licenses/MIT>
-- @added 0.9.0

local io, load, tonumber, pcall, table, os, string, require = io, load, tonumber, pcall, table, os, string, require
local cfg = require"configi"
local lib = require"lib"
local crc = require"crc32"
local stat = require"posix.sys.stat"
local cmd = lib.cmd
local textfile = {}
local ENV = {}
_ENV = ENV

local main = function (S, M, G)
  local C = cfg.start(S, M, G)
  C.required = { "path" }
  C.alias.src = { "template" }
  C.alias.path = { "dest", "file", "textfile" }
  C.alias.lua = { "data" }
  C.alias.table = { "view" }
  C.alias.line = { "text" }
  C.alias.pattern = { "match" }
  return cfg.finish(C)
end

local write = function (F, P, R)
  -- ignore P.diff if diffutils is not found
  if not lib.binpath("diff") then P.diff = false end
  if (P.debug or P.test) and P.diff then
    local temp = os.tmpname()
    if lib.awrite(temp, P._input, 384) then
      local dtbl = {}
      local res, diff = cmd.diff{ "-N", "-a", "-u", P.path, temp }
      os.remove(temp)
      if res then
        return F.kept(P.path)
      else
        for n = 1, #diff.stdout do
          dtbl[n] = string.match(diff.stdout[n], "[%g%s]+") or ""
        end
        F.msg(P.path, "Showing changes", 0, 0, string.format("Diff:%s%s%s", "\n\n", table.concat(dtbl, "\n"), "\n"))
      end
    else
      return F.result(P.path, false)
    end
  end
  return F.result(P.path, lib.awrite(P.path, P._input, P.mode))
end

--- Render a textfile.
-- @note Requires the diffutils package for the diff parameter to work
-- @param path output file [REQUIRED] [ALIAS: dest,file,textfile]
-- @param src source template [REQUIRED] [ALIAS: template]
-- @param table [REQUIRED] [ALIAS: view]
-- @param lua [ALIAS: data]
-- @param mode mode bits for output file [DEFAULT: "0600"]
-- @param diff show diff [CHOICES: "yes","no"]
-- @usage textfile.render [[
--   template "/etc/something/config.template"
--   dest "/etc/something/config"
--   view "view_model"
--   data "/etc/something/config.lua"
-- ]]
function textfile.render (S)
  local M = { "src", "lua", "table", "mode", "diff" }
  local G = {
    repaired = "textfile.render: Successfully rendered textfile.",
    kept = "textfile.render: No difference detected, not overwriting existing destination.",
    failed = "textfile.render: Error rendering textfile.",
    missingsrc = "textfile.render: Can't access or missing source file.",
    missinglua = "textfile.render: Can't access or missing lua file."
  }
  local F, P, R = main(S, M, G)
  P.mode = P.mode or "0600"
  P.mode = tonumber(P.mode, 8)
  local ti = F.open(P.src)
  if not ti then
    return F.result(P.src, false, G.missingsrc)
  end
  local lua = F.open(P.lua)
  if not lua then
    return F.result(P.lua, false, G.missinglua)
  end
  local env = { require = require }
  local tbl
  local ret, chunk, err = pcall(load, lua, lua, "t", env)
  if ret and chunk then
    chunk()
    tbl = env[P.table]
  else
    return F.result(P.src, false, err)
  end
  P._input = lib.sub(ti, tbl)
  if stat.stat(P.path) then
    do -- compare P.path and rendered text
      local i
      for b in io.lines(P.path, 2^12) do
        if i == nil then
         i = crc.crc32_string(b)
        else
         i = crc.crc32(b, crc.crc32(i))
        end
      end
      if i == crc.crc32_string(P._input) then
        return F.kept(P.path)
      end
    end
  end
  return write(F, P, R)
end

--- Insert lines into an existing file.
-- @param path path of textfile to modify [REQUIRED] [ALIAS: dest,file,textfile]
-- @param line text to insert [REQUIRED] [ALIAS: text]
-- @param inserts a line (string) if found, skips the operation
-- @param pattern line is added before or after this pattern [ALIAS: match]
-- @param plain turn on or off pattern matching facilities [CHOICES: "yes","no"] [DEFAULT: "yes"]
-- @param before [CHOICES: "yes","no"] [DEFAULT: "no"]
-- @param after [CHOICES: "yes","no"] [DEFAULT: "yes"]
-- @usage textfile.insert_line [[
--   path "/etc/sysctl.conf"
--   pattern "# http://cr.yp.to/syncookies.html"
--   text "net.ipv4.tcp_syncookies = 1"
--   after "true"
--   plain "true"
-- ]]
function textfile.insert_line (S)
  local M = { "diff", "line", "plain", "pattern", "before", "after", "inserts" }
  local G = {
    repaired = "textfile.insert_line: Successfully inserted line.",
    kept = "textfile.insert_line: Insert cancelled, found a matching line.",
    failed = "textfile.insert_line: Error inserting line.",
    missing = "textfile.insert_line: Can't access or missing file."
  }
  local F, P, R = main(S, M, G)
  P.plain = P.plain or true
  local inserts, line, pattern
  if not P.plain then
    inserts = lib.escape_pattern(P.inserts)
    line = lib.escape_pattern(P.line)
    pattern = lib.escape_pattern(P.pattern)
  else
    inserts = P.inserts
    line = P.line
    pattern = P.pattern
  end
  local file = lib.file_to_tbl(P.path)
  if not file then
    return F.result(P.path, false, G.missing)
  end
  P.mode = stat.stat(P.path).st_mode
  if P.inserts then
    if lib.find_string(file, inserts, P.plain) then
      return F.kept(P.path)
    end
  end
  if not P.pattern then
    if lib.find_string(file, line, P.plain) then
      return F.kept(P.path)
    else
      file[#file + 1] = P.line .. "\n"
    end
  else
    local x, n, nf = 1, 1, #file
    if P.before then -- after "yes" is default
      x = 0
    end
    repeat
      if string.find(file[n], pattern, 1, P.plain) then
        table.insert(file, n + x, P.line .. "\n")
        nf = nf + 1
        n = n + 2
      else
        n = n + 1
      end
    until n == nf
  end
  P._input = table.concat(file)
  return write(F, P, R)
end

--- Remove lines from an existing file.
-- @param path path of textfile to modify [REQUIRED] [ALIAS: dest,file,textfile]
-- @param pattern text pattern to remove [REQUIRED] [ALIAS: match]
-- @param plain turn on or off pattern matching facilities [CHOICES: "yes","no"] [DEFAULT: "yes"]
-- @usage textfile.remove_line [[
--   path "/etc/sysctl.conf"
--   match "net.ipv4.ip_forward = 1"
--   plain "true"
-- ]]
function textfile.remove_line (S)
  local M = { "pattern", "plain", "diff" }
  local G = {
    repaired = "textfile.remove_line: Successfully removed line.",
    kept = "textfile.remove_line: Line not found.",
    failed = "textfile.remove_line: Error removing line.",
    missing = "textfile.remove_line: Can't access or missing file."
  }
  local F, P, R = main(S, M, G)
  P.plain = P.plain or true
  local pattern
  if not P.plain then
    pattern = lib.escape_pattern(P.pattern)
  else
    pattern = P.pattern
  end
  local file = lib.file_to_tbl(P.path)
  if not file then
    return F.result(P.path, false, G.missing)
  end
  P.mode = stat.stat(P.path).st_mode
  if not lib.find_string(file, pattern, P.plain) then
    return F.kept(P.path)
  end
  P._input = table.concat(lib.filter_tbl_value(file, pattern, P.plain))
  return write(F, P, R)
end

return textfile
