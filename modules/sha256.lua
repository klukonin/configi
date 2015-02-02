-- Verify the SHA256 hash of a file.
-- @module sha256
-- @author Eduardo Tongson <propolice@gmail.com>
-- @license MIT <http://opensource.org/licenses/MIT>
-- @added 0.9.6

local Lua = {
  lines = io.lines
}
local Configi = require"configi"
local sha2 = require"sha2"
local Pstat = require"posix.sys.stat"
local Lc = require"cimicida"
local sha256 = {}
local ENV = {}
_ENV = ENV

local main = function (S, M, G)
  local C = Configi.start(S, M, G)
  C.required = { "path", "hash" }
  C.alias.path = { "file" }
  C.alias.hash = { "digest", "signature" }
  return Configi.finish(C)
end

--- Check that a given hash matches the actual SHA256 hash of a file.
-- <br />
-- Useful for alerting on changed hashes
-- @alias check
-- @param path path of file to hash [ALIAS: file] [REQUIRED]
-- @param hash the 32-byte alphanumeric string to match for [ALIAS: digest,signature] [REQUIRED]
-- @usage sha256.verify [[
--   path "/etc/passwd"
--   hash "09e40b7b232c4abb427f1344e636e44ebf5684f70fb6cd67507e88955064255d"
-- ]]
function sha256.verify (S)
  local G = {
    ok = "sha256.verify: Hash matched.",
    skip = "sha256.verify: Hash matched.",
    fail = "sha256.verify: Hash mismatch.",
    missing = "sha256.verify: Missing path."
  }
  local F, P, R = main(S, M, G)
  if not Pstat.stat(P.path) then
    return F.result(P.path, false, G.missing)
  end
  local S = sha2.new256()
  for f in Lua.lines(P.path, 2^12) do
    S:add(f)
  end
  if S:close() ==  P.hash then
    return F.skip(P.path)
  else
    return F.result(P.path, false)
  end
end

sha256.check = sha256.verify
return sha256