#!/bin/bash
clear
set -ex

# https://www.libsdl.org/

cd "$VCPKG_ROOT"
sudo git pull
sudo ./vcpkg install sdl2 sdl2-ttf sdl2-mixer sdl2-image sdl2-gfx
