#!/bin/sh

set -e

USE_CLANG=1

if [[ "${USE_CLANG}" -eq 1 ]]; then
    export CC=/usr/bin/clang
    export CXX=/usr/bin/clang++
    CFLAGS="${CFLAGS} -Qunused-arguments"
    CXXFLAGS="${CXXFLAGS} -std=c++11 -Qunused-arguments -O0"
else
    CXXFLAGS="${CXXFLAGS} -std=c++0x -O0"
fi

BUILD_DIR=$(dirname ${BASH_SOURCE[0]})
cd "${BUILD_DIR}/../../src"
ctags -R .
cd "${BUILD_DIR}"

mkdir -p bin
cmake CMakeLists.txt
make -j8

cd bin
ln -sf ../../../src/engine/platforms/linux/shaders
../../../tools/AtlasGen/AtlasGen.py -r ../../../resources -m RGBA -t tga

rm -rfv grids
cp -rv ../../../resources/grids grids

gdb ./ponic
