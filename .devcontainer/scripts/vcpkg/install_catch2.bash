#!/bin/bash
clear
set -ex

# https://github.com/catchorg/Catch2

cd "$VCPKG_ROOT"
sudo git pull
sudo ./vcpkg install catch2
