#!/bin/bash
clear
set -ex

# https://invisible-island.net/ncurses/
# https://github.com/ThomasDickey/ncurses-snapshots

cd "$VCPKG_ROOT"
sudo git pull
sudo ./vcpkg install ncurses
