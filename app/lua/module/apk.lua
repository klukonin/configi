-- Ensure that an apk managed package is present, absent or updated.
-- @module apk
-- @author Eduardo Tongson <propolice@gmail.com>
-- @license MIT <http://opensource.org/licenses/MIT>
-- @added 0.9.0

local cfg = require"configi"
local lib = require"lib"
local cmd = lib.cmd
local apk = {}
local ENV = {}
_ENV = ENV

local main = function (S, M, G)
  local C = cfg.start(S, M, G)
  C.required = { "package" }
  return cfg.finish(C)
end

local found = function (package)
  local _, out = cmd["/sbin/apk"]{ "version", package }
  if lib.find_string(out.stdout, package, true) then
    return true
  end
end

--- Install a package via apk
-- See `apk help` for full description of options and parameters
-- @aliases installed
-- @aliases install
-- @param package name of the package to install [REQUIRED]
-- @param update_cache update cache before adding package [CHOICES: true, false, "yes", "no"] [DEFAULT: "no", false]
-- @usage apk.present {
--   package = "strace"
--   update_cache = true
-- }
function apk.present (S)
  local M = { "update_cache" }
  local G = {
    repaired = "apk.present: Successfully installed package.",
    kept = "apk.present: Package already installed.",
    failed = "apk.present: Error installing package."
  }
  local F, P, R = main(S, M, G)
  if found(P.package) then
    return F.kept(P.package)
  end
  local args = { "add", "--no-progress", "--quiet", P.package }
  lib.insert_if(P.update_cache, args, 2, "--update-cache")
  return F.result(P.package, F.run(cmd["/sbin/apk"], args))
end

--- Remove a package
-- @aliases removed
-- @aliases remove
-- @param package name of the package to remove [REQUIRED]
function apk.absent (S)
  local G = {
    repaired = "apk.absent: Successfully removed package",
    kept = "apk.absent: Package not installed.",
    failed = "apk.absent: Error removing package."
  }
  local F, P, R = main(S, M, G)
  if not found(P.package) then
    return F.kept(P.package)
  end
  return F.result(P.package, F.run(cmd["/sbin/apk"], { "del", "--no-progress", "--quiet", P.package }))
end

apk.installed = apk.present
apk.install = apk.present
apk.removed = apk.absent
apk.remove = apk.absent
return apk
