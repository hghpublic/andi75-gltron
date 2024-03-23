#!/bin/bash
clear
set -ex

# https://github.com/nothings/stb

cd "$VCPKG_ROOT"
sudo git pull
sudo ./vcpkg install stb
