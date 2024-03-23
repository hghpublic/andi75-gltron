#!/bin/bash
clear
set -ex

USER=vscode
HOME=/home/$USER

echo "alias cls='clear'" >> $HOME/.bashrc
