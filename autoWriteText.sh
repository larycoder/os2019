#!/bin/sh
echo "$@: ">>01.report.shell.commands.txt
eval "$@|head -n 10">>01.report.shell.commands.txt
echo "--------------------">>01.report.shell.commands.txt
