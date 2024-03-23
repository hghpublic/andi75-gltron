#!/bin/bash
clear
set -ex

# https://www.sfml-dev.org/

cd "$VCPKG_ROOT"
sudo git pull
sudo ./vcpkg install sfml
