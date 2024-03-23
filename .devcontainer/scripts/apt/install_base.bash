#!/bin/bash
clear
set -ex

# https://docs.docker.com/develop/develop-images/dockerfile_best-practices/

apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        expect \
        fish \
        imagemagick \
        mc \
        python3-autopep8 \
        shellcheck \
        speedtest-cli \
        tree \
    && rm -rf /var/lib/apt/lists/*
