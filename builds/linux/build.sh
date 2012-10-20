#!/bin/sh

set -e

# FIXME: I hate fixed paths too, ya
cd ~/coding/github/ponic/builds/linux

mkdir -p bin
cmake CMakeLists.txt
make -j4

cd bin
ln -sf ../../../src/engine/shaders
../../../tools/AtlasGen/AtlasGen.py -r ../../../resources -m RGBA -t tga

gdb ./ponic
