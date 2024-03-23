#!/bin/bash
clear
set -ex

# https://github.com/ocornut/imgui

cd "$VCPKG_ROOT"
sudo git pull
sudo ./vcpkg install --recurse imgui[core,sdl2-binding,sdl2-renderer-binding,opengl3-binding]
