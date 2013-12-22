#!/bin/sh

set -e

export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

CFLAGS="${CXXFLAGS} -Qunused-arguments"
CXXFLAGS="${CXXFLAGS} -std=c++11 -Qunused-arguments"

BUILD_DIR=$(dirname ${BASH_SOURCE[0]})
cd "${BUILD_DIR}/../../src"
ctags -R .
cd "${BUILD_DIR}"

if [ ! -f ../../src/all.h ]; then
    ../../src/gen_all.sh
fi

mkdir -p bin
cmake CMakeLists.txt
make -j8

cd bin
ln -sf ../../../src/engine/platforms/linux/shaders
../../../tools/AtlasGen/AtlasGen.py -r ../../../resources -m RGBA -t tga

rm -rfv grids
cp -rv ../../../resources/grids grids

gdb ./ponic
