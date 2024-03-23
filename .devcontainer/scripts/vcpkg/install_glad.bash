#!/bin/bash
clear
set -ex

# https://github.com/Dav1dde/glad

cd "$VCPKG_ROOT"
sudo git pull
sudo ./vcpkg install glad
