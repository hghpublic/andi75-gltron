#!/bin/bash
clear
set -ex

repo=entt
cd /workspaces/$repo/.devcontainer/scripts/vcpkg

./install_catch2.bash > install_catch2.log
./install_cereal.bash > install_cereal.log
./install_cr.bash > install_cr.log
./install_entt.bash > install_entt.log
./install_fmt.bash > install_fmt.log
./install_glad.bash > install_glad.log
./install_gsl.bash > install_gsl.log
./install_gtest.bash > install_gtest.log
./install_imgui.bash > install_imgui.log
# ./install_ncurses.bash > install_ncurses.log
./install_opengl.bash > install_opengl.log
./install_sdl.bash > install_sdl.log
./install_sfml.bash > install_sfml.log
./install_stb.bash > install_stb.log
