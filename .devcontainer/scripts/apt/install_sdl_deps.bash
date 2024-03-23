#!/bin/bash
clear
set -ex

# https://docs.docker.com/develop/develop-images/dockerfile_best-practices/
# autoconf

apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        autoconf \
        libgles2-mesa-dev \
        libxext-dev \
    && rm -rf /var/lib/apt/lists/*
