#!/bin/bash
clear
set -ex

# https://docs.docker.com/develop/develop-images/dockerfile_best-practices/
# autoconf
# apt-get install libx11-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev libgl1-mesa-dev

apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        autoconf \
        automake \
        autotools-dev \
        libopengl-dev \
        libtool \
        libudev-dev \
        libx11-dev \
        libxcursor-dev \
        libxrandr-dev \
    && rm -rf /var/lib/apt/lists/*
