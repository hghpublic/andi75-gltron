#!/bin/bash
clear
# set -ex
set -e

uname -a
lsb_release -a
# nproc
# lscpu
lscpu | grep -E '^Thread|^Core|^Socket|^CPU\('
free -mh
# cat /proc/cpuinfo
# grep -E 'processor|core id' /proc/cpuinfo
# grep -m 1 'cpu cores' /proc/cpuinfo
# cat /proc/meminfo
# cat /proc/vmstat
# cat /proc/loadavg
# getconf _NPROCESSORS_ONLN
# sudo dmidecode -t 4
echo "USER: ${USER}"
echo "DISPLAY: ${DISPLAY}"
echo "XDG_RUNTIME_DIR: ${XDG_RUNTIME_DIR}"
echo "PATH: ${PATH}"
sudo du -sh --exclude /proc /
sudo du -sh /home/vscode/
sudo du -sh /workspaces/
