--- Ensure that a package managed by Portage is installed or absent.
-- @module portage
-- @author Eduardo Tongson <propolice@gmail.com>
-- @license MIT <http://opensource.org/licenses/MIT>
-- @added 0.9.0

local string, table = string, table
local lib = require"lib"
local cmd = lib.cmd
local stat = require"posix.sys.stat"
local dirent = require"posix.dirent"
local portage = {}
local ENV = {}
_ENV = ENV

local main = function (S, M, G)
  local C = cfg.start(S, M, G)
  C.required = { "atom" }
  C.alias.atom = { "package" }
  return cfg.finish(C)
end

local decompose = function (P)
  local A = {}
  if string.find(P.atom, "^[%<%>%=]+%g*$") then
    -- package ">=net-misc/rsync-3.0.9-r3"
    A.lead = string.match(P.atom, "[%<%>%=]+") -- >=
    A.category, A.package = lib.split_path(P.atom) -- >=net-misc, rsync-3.0.9-r3
    A.category = string.match(A.category, "[%<%>%=]+([%w%-]+)") -- net-misc
    A.version = "" -- version is already at the end of A.package
    --[[
    A.revision = string.match(A.package, "%-(r[%d]+)", -3) -- r3
    A.version = string.match(A.package, "[%w%-]+%-([%d%._]+)%-" .. A.revision) -- 3.0.9
    A.package = string.match(A.package, "([%w%-]+)" .. "%-" .. A.version .. "%-" .. A.revision) -- rsync
    ]]
  elseif P.version then
    --[[
      package "net-misc/rsync"
      version ">=3.0.9-r3"
    ]]
    A.lead = string.match(P.version, "[%<%>%=]+")
    A.category, A.package = lib.split_path(P.atom)
    A.version = string.match(P.version, "[%<%>%=]+([%g]+)")
    A.version = "-" .. A.version
    if A.lead == nil then
      A.lead = "="
    end
  else
    -- package "net-misc/rsync"
    A.category, A.package = lib.split_path(P.atom)
    A.lead, A.version = "", ""
  end
  return A
end

local found = function (P)
  local A = decompose(P)
  if lib.isdir("/var/db/pkg/" .. A.category) then
    if A.lead == "" then
      -- package "net-misc/rsync"
      for packages in dirent.files("/var/db/pkg/" .. A.category) do
        if string.find(packages, "^" .. A.package .. "%-%g*$") then
          return true
        end
      end
    else
      if stat.stat(string.format("/var/db/pkg/%s/%s%s", A.category, A.package, A.version)) then
        return true
      end
    end
  end
end

--- Install package atom.
--- See emerge(1).
-- @aliases installed
-- @aliases install
-- @param atom package atom to install. Can be "category/package" or "category/package-version" [REQUIRED] [ALIAS: package]
-- @param version package version
-- @param deep evaluate entire dependency tree [CHOICES: "yes","no"]
-- @param newuse reinstall packages that had a change in its USE flags [CHOICES: "yes","no"]
-- @param nodeps do not merge dependencies [CHOICES: "yes","no"]
-- @param noreplace skip already installed packages [CHOICES: "yes","no"]
-- @param oneshot do not update the world file [CHOICES: "yes","no"] [DEFAULT: "yes"]
-- @param onlydeps only merge dependencies [CHOICES: "yes","no"]
-- @param sync perform an `emerge --sync` before installing package(s) [CHOICES: "yes","no"]
-- @param update update package to the best version [CHOICES: "yes","no"]
-- @param unmask enable auto-unmask and auto-unmask-write options [CHOICES: "yes","no"]
-- @usage portage.present [[
--   package "dev-util/strace"
--   version "4.8"
-- ]]
-- portage.present [[
--   atom "=dev-util/strace-4.8"
-- ]]
-- portage.present [[
--   package "dev-util/strace"
-- ]]
function portage.present (S)
  local M = { "deep", "newuse", "nodeps", "noreplace", "oneshot", "onlydeps", "sync", "unmask", "update", "version" }
  local G = {
    repaired = "portage.present: Successfully installed package.",
    kept = "portage.present: Package already installed.",
    failed = "portage.present: Error installing package."
  }
  local F, P, R = main(S, M, G)
  if P.oneshot == nil then
    P.oneshot = true -- oneshot "yes" is default
  end
  -- `emerge --sync` mode
  if P.sync == true then
    if F.run(cmd["/usr/bin/emerge"], { "--sync" }) then
      F.msg("sync", "Sync finished", true)
    else
      return F.result("sync", false, "Sync failed")
    end
  end
  if found(P) then
    return F.kept(P.atom)
  end
  local A = decompose(P)
  local atom = string.format("%s%s/%s%s", A.lead or "", A.category, A.package, A.version)
  local args = { "--quiet", "--quiet-build", atom }
  lib.insert_if(P.deep, args, 3, "--deep")
  lib.insert_if(P.newuse, args, 3, "--newuse")
  lib.insert_if(P.nodeps, args, 3, "--nodeps")
  lib.insert_if(P.noreplace, args, 3, "--noreplace")
  lib.insert_if(P.oneshot, args, 3, "-1")
  lib.insert_if(P.onlydeps, args, 3, "--onlydeps")
  if P.unmask then
    table.insert(args, 3, "--auto-unmask-write")
    table.insert(args, 3, "--auto-unmask")
    if not F.run(cmd["/usr/bin/emerge"], args) then
      return F.result(atom, false, G.failed)
    end
    table.remove(args, 3)
    table.remove(args, 3)
  end
  return F.result(atom, F.run(cmd["/usr/bin/emerge"], args))
end

--- Remove package atom.
-- @aliases remove
-- @param atom package atom to unmerge [REQUIRED] [ALIAS: package]
-- @param depclean Remove packages not associated with explicitly installed packages [CHOICES: "yes","no"] [DEFAULT: "no"]
-- @usage portage.absent [[
--   atom "dev-util/atom"
-- ]]
function portage.absent (S)
  local M = { "depclean" }
  local G = {
    repaired = "portage.absent: Successfully removed package.",
    kept = "portage.absent: Package not installed.",
    failed = "portage.absent: Error removing package."
  }
  local F, P, R = main(S, M, G)
  if not found(P) then
    return F.kept(P.atom)
  end
  local env = { "CLEAN_DELAY=0", "PATH=/bin:/usr/bin:/sbin:/usr/sbin" } -- PORTAGE_BZIP2_COMMAND needs $PATH
  local A = decompose(P)
  local atom = string.format("%s%s/%s%s", A.lead or "", A.category, A.package, A.version)
  local args = { _env = env, "--quiet", "-C", atom }
  lib.insert_if(P.depclean, args, 2, "--depclean")
  return F.result(atom, F.run(cmd["/usr/bin/emerge"], args))
end

portage.installed = portage.present
portage.install = portage.present
portage.remove = portage.absent
return portage
