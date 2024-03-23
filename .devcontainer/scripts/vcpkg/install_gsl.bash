#!/bin/bash
clear
set -ex

# https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
# https://github.com/microsoft/GSL

cd "$VCPKG_ROOT"
sudo git pull
sudo ./vcpkg install ms-gsl
