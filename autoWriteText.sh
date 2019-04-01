#!/bin/sh
echo "$@: ">>01.report.report.shell.commands.dm
eval "$@|head -n 10">>01.report.report.shell.commands.dm
