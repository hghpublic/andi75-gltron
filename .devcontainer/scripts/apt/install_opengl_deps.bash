#!/bin/bash
clear
set -ex

# https://docs.docker.com/develop/develop-images/dockerfile_best-practices/


apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        libglu1-mesa-dev \
        mesa-common-dev \
    && rm -rf /var/lib/apt/lists/*
