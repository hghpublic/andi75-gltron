#!/bin/bash
clear
set -ex

# https://docs.docker.com/develop/develop-images/dockerfile_best-practices/

apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        libsdl2-dev \
        libsdl2-image-dev \
        libsdl2-mixer-dev \
        libsdl2-ttf-dev \
    && rm -rf /var/lib/apt/lists/*
