#!/bin/bash
clear
set -ex

# https://github.com/skypjack/entt

cd "$VCPKG_ROOT"
sudo git pull
sudo ./vcpkg install entt
