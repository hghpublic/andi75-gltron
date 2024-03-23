#!/bin/bash
clear
set -ex

# https://www.opengl.org/

cd "$VCPKG_ROOT"
sudo git pull
sudo ./vcpkg install opengl
