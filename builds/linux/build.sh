#!/bin/sh

set -e

export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

CXXFLAGS="${CXXFLAGS} -std=c++0x"

BUILD_DIR=$(dirname ${BASH_SOURCE[0]})
cd "${BUILD_DIR}"

mkdir -p bin
cmake CMakeLists.txt
make -j4

cd bin
ln -sf ../../../src/engine/platforms/linux/shaders
../../../tools/AtlasGen/AtlasGen.py -r ../../../resources -m RGBA -t tga

gdb ./ponic
