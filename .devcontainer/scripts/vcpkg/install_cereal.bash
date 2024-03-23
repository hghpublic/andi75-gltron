#!/bin/bash
clear
set -ex

# https://uscilab.github.io/cereal/

cd "$VCPKG_ROOT"
sudo git pull
sudo ./vcpkg install cereal
