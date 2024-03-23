#!/bin/bash
clear
set -ex

find . -type d -name  build -print
# if [ -d build ]; then rm -rf build; fi
# mkdir build

# $ find . -name "*.txt" -exec ls -al {} \;
# $ find . -name "*.txt" | xargs ls -al


# for dir in $(find . -type d -name  build -print)
# do
#     echo "dir ${dir}"
# done

WORKSPACE_DIR=/workspaces/entt
find ${WORKSPACE_DIR} -type d -name build -exec rm -rf {} \;
