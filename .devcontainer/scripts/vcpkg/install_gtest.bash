#!/bin/bash
clear
set -ex

# https://github.com/google/googletest

cd "$VCPKG_ROOT"
sudo git pull
sudo ./vcpkg install gtest
