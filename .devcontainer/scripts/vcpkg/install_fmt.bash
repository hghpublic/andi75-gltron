#!/bin/bash
clear
set -ex

# https://github.com/fmtlib/fmt

cd "$VCPKG_ROOT"
sudo git pull
sudo ./vcpkg install fmt
