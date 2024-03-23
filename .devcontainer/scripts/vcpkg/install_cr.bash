#!/bin/bash
clear
set -ex

# https://github.com/fungos/cr

cd "$VCPKG_ROOT"
sudo git pull
sudo ./vcpkg install cr
