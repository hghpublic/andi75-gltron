# https://mcr.microsoft.com/v2/devcontainers/cpp/tags/list
# https://github.com/devcontainers/images/tree/main/src/cpp/history
ARG GET_ALL_NON_BREAKING_CHANGES=1
ARG ONLY_GET_FIXES=1.2
FROM mcr.microsoft.com/devcontainers/cpp:${GET_ALL_NON_BREAKING_CHANGES}-ubuntu-24.04

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.30.5"

# Optionally install the cmake for vcpkg
COPY ./reinstall-cmake.sh /tmp/

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

# [Optional] Uncomment this section to install additional vcpkg ports.
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install <your-port-name-here>"

# [Optional] Uncomment this section to install additional packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>

# dev
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        gcc-14 g++-14 \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/* \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 1 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-14 1

# tools
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        ascii \
        cmake-format \
        dialog \
        expect \
        feh \
        file \
        fish \
        hwinfo \
        mc \
        netpbm \
        rename \
        scrot \
        shellcheck \
        tree \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# audio
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        alsa-base \
        alsa-utils \
        beep \
        libsndfile1-dev \
        pulseaudio \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# SDL2
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        libltdl-dev \
        python3-jinja2 \
        libx11-dev libxft-dev libxext-dev \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# dxx-rebirth deps
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends \
#         scons libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libphysfs-dev \
#     && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# # stella
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends \
#         bison \
#     && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# SDL1 deps
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends \
#         libsdl1.2-dev libsdl-image1.2-dev libsdl-gfx1.2-dev \
#     && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# SDL2 deps
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends \
#         libglu1-mesa-dev \
#         libx11-dev libxft-dev libxext-dev \
#     && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# https://docs.docker.com/develop/develop-images/dockerfile_best-practices/

ARG SCRIPTS_DIR=/tmp/scripts
COPY scripts $SCRIPTS_DIR
RUN $SCRIPTS_DIR/apt/install_base.bash \
    && $SCRIPTS_DIR/apt/install_opengl_deps.bash \
    && $SCRIPTS_DIR/apt/install_sdl_deps.bash \
    && $SCRIPTS_DIR/apt/install_sdl1.bash \
    && $SCRIPTS_DIR/apt/install_gnome_deps.bash \
    && $SCRIPTS_DIR/apt/install_sfml_deps.bash \
    && $SCRIPTS_DIR/config/config_system.bash

# gdb pretty printers
USER vscode
RUN cp $SCRIPTS_DIR/gdb/.gdbinit /home/vscode/.gdbinit

# https://docs.github.com/en/codespaces/developing-in-codespaces/default-environment-variables-for-your-codespace
# ENV WORKSPACE_DIR=/workspaces/descent
# ENV DESCENT_DIR=${WORKSPACE_DIR}/descent
