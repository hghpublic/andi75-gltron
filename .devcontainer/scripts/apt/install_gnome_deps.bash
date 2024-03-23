#!/bin/bash
clear
set -ex

# https://docs.docker.com/develop/develop-images/dockerfile_best-practices/

apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        bison \
        libx11-dev \
        libgles2-mesa-dev \
        libxi-dev \
        libxdamage-dev \
        libxinerama-dev \
    && rm -rf /var/lib/apt/lists/*
