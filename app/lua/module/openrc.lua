--- Ensure that an OpenRC service is started or stopped.
-- <br />
-- This module can also restart and reload a service.
-- <br />
-- And add or remove a service from a particular runlevel.
-- @module openrc
-- @author Eduardo Tongson <propolice@gmail.com>
-- @license MIT <http://opensource.org/licenses/MIT>
-- @added 0.9.0

local cfg = require"configi"
local lib = require"lib"
local cmd = lib.cmd
local openrc = {}
local ENV = {}
_ENV = ENV

local main = function (S, M, G)
  local C = cfg.start(S, M, G)
  C.required = { "service" }
  C.alias.service = { "daemon" }
  return cfg.finish(C)
end

--- Start a service.
-- @aliases present
-- @param service service to start [REQUIRED]
-- @usage openrc.started [[
--   service "rsyncd"
-- ]]
function openrc.started (S)
  local G = {
    repaired = "openrc.started: Successfully started service.",
    kept = "openrc.started: Service already started.",
    failed = "openrc.started: Error starting service"
  }
  local F, P, R = main(S, M, G)
  local code, out, test = F.run(cmd["/bin/rc-status"], { "--nocolor", "--servicelist", _return_code = true })
  local pattern = "^%s" .. lib.escape_pattern(P.service) .. "%s*%[%s%sstarted%s%s%]$"
  if test or ((code ==0) and (lib.find_string(out.stdout, pattern))) then
    return F.kept(P.service)
  end
  local start =
    F.run(cmd["/sbin/rc-service"], { "--nocolor", "--quiet", P.service, "start", _return_code = true })
  return F.result(P.service, (start == 0))
end

--- Stop a service.
-- @aliases absent
-- @param service service to stop [REQUIRED]
-- @usage openrc.stopped [[
--   service "rsyncd"
-- ]]
function openrc.stopped (S)
  local G = {
    repaired = "openrc.stopped: Successfully stopped service.",
    kept = "openrc.stopped: Service already stopped.",
    failed = "openrc.stopped: Error stopping service."
  }
  local F, P, R = main(S, M, G)
  local code, out, test = F.run(cmd["/bin/rc-status"], { "--nocolor", "--servicelist", _return_code = true })
  local pattern = "^%s" .. lib.escape_pattern(P.service) .. "%s*%[%s%sstarted%s%s%]$"
  if test or ((code == 0) and not (lib.find_string(out.stdout, pattern))) then
    return F.kept(P.service)
  end
  local stop = F.run(cmd["/sbin/rc-service"], { "--nocolor", "--quiet", P.service, "stop", _return_code = true })
  return F.result(P.service, (stop == 0))
end

--- Restart a service.
-- @param service service to restart [REQUIRED]
-- @usage openrc.restart [[
--   service "rsyncd"
-- ]]
function openrc.restart (S)
  local G = {
    repaired = "openrc.restart: Successfully restarted service.",
    failed = "openrc.restart: Error restarting service."
  }
  local F, P, R = main(S, M, G)
  local code, _, test =
    F.run(cmd["/sbin/rc-service"], { "--nocolor", "--quiet", P.service, "restart", _return_code = true })
  if test or (code == 0) then
    return F.result(P.service, true)
  end
end

--- Reload a service.
-- @param service service to reload [REQUIRED]
-- @usage openrc.reload [[
--   service "sshd"
-- ]]
function openrc.reload (S)
  local G = {
    repaired = "openrc.reload: Successfully reloaded service",
    failed = "openrc.reload: Error reloading service."
  }
  local F, P, R = main(S, M, G)
  local code, _, test =
    F.run(cmd["/sbin/rc-service"], { "--nocolor", "--quiet", P.service, "reload", _return_code = true })
  if test or (code == 0) then
    return F.result(P.service, true)
  end
end

--- Add a service to runlevel.
-- @param service service to add [REQUIRED]
-- @param runlevel runlevel to add to [REQUIRED] [DEFAULT: default]
-- @usage openrc.add [[
--   service "rsyncd"
--   runlevel "default"
-- ]]
function openrc.add (S)
  local M = { "runlevel" }
  local G = {
    repaired = "openrc.add: Successfully added service to runlevel.",
    kept = "openrc.add: Service already in the runlevel.",
    failed = "openrc.add: Error adding service to runlevel."
  }
  local F, P, R = main(S, M, G)
  P.runlevel = P.runlevel or "default"
  local _
  local code, out, test =
    F.run(cmd["/sbin/rc-update"], { "--nocolor", "--quiet", "show", P.runlevel, _return_code = true })
  local pattern = "^%s*" .. lib.escape_pattern(P.service) .. "%s|%s" .. P.runlevel .. "%s*$"
  if test or ((code == 0) and lib.find_string(out.stdout, pattern)) then
    return F.kept(P.service)
  end
  code, _, test =
    F.run(cmd["/sbin/rc-update"], { "--nocolor", "--quiet", "add", P.service, P.runlevel, _return_code = true })
  return F.result(P.service, (test or (code == 0)))
end

--- Remove a service from a runlevel.
-- @aliases del
-- @param service service to remove [REQUIRED] [ALIAS: daemon]
-- @param runlevel runlevel to remove from [REQUIRED] [DEFAULT: default]
-- @usage openrc.delete [[
--   service "rsyncd"
--   runlevel "default"
-- ]]
function openrc.delete (S)
  local M = { "runlevel" }
  local G = {
    repaired = "openrc.delete: Successfully deleted service from runlevel.",
    kept = "openrc.delete: Service already absent from runlevel.",
    failed = "openrc.delete: Error deleting service from runlevel."
  }
  local F, P, R = main(S, M, G)
  P.runlevel = P.runlevel or "default"
  local _
  local code, out, test =
    F.run(cmd["/sbin/rc-update"], { "--nocolor", "--quiet", "show", P.runlevel, _return_code = true })
  local pattern = "^%s*" .. lib.escape_pattern(P.service) .. "%s|%s" .. P.runlevel .. "%s*$"
  if test or ((code == 0) and not (lib.find_string(out.stdout, pattern))) then
    return F.kept(P.service)
  end
  code, _, test =
    F.run(cmd["/sbin/rc-update"], { "--nocolor", "--quiet", "del", P.service, P.runlevel, _return_code = true })
  return F.result(P.service, (test or (code == 0)))
end

openrc.present = openrc.started
openrc.absent = openrc.stopped
openrc.del = openrc.delete
return openrc

