#!/bin/bash
clear
set -ex

# https://docs.docker.com/develop/develop-images/dockerfile_best-practices/

# https://emscripten.org/
# https://emscripten.org/docs/getting_started/downloads.html
USER=vscode
USERHOME=/home/$USER
EMSDK_DIR=$USERHOME/emsdk
cd $USERHOME
# Get the emsdk repo
git clone https://github.com/emscripten-core/emsdk.git
# Enter that directory
cd $EMSDK_DIR
# Fetch the latest version of the emsdk (not needed the first time you clone)
git pull
# Download and install the latest SDK tools.
./emsdk install latest
# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
./emsdk activate latest
# Activate PATH and other environment variables in the current terminal
# source ./emsdk_env.sh
chown $USER:$USER -R $EMSDK_DIR
echo "EMSDK_DIR=$EMSDK_DIR" >> $USERHOME/.bashrc
echo "source $EMSDK_DIR/emsdk_env.sh" >> $USERHOME/.bashrc
