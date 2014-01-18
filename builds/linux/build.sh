#!/bin/sh

set -e

USE_CLANG=1
DEBUG=1

if [[ "${DEBUG}" -eq 1 ]]; then
    CFLAGS="${CFLAGS} -O0 -g -rdynamic -D_DEBUG"
    CXXFLAGS="${CXXFLAGS} -O0 -g -rdynamic -D_DEBUG"
else
    CFLAGS="-O2"
    CXXFLAGS="${CFLAGS}"
fi

if [[ "${USE_CLANG}" -eq 1 ]]; then
    export CC=/usr/bin/clang
    export CXX=/usr/bin/clang++
    CFLAGS="${CFLAGS} -Qunused-arguments"
    CXXFLAGS="${CXXFLAGS} -std=c++11 -Qunused-arguments"
else
    CXXFLAGS="${CXXFLAGS} -std=c++0x"
fi

BUILD_DIR=$(dirname ${BASH_SOURCE[0]})
cd "${BUILD_DIR}/../../src"
ctags -R .
cd "${BUILD_DIR}"

mkdir -p bin
cmake CMakeLists.txt
#make -j8 VERBOSE=1
make -j8

cd bin
ln -sf ../../../src/engine/platforms/linux/shaders
../../../tools/AtlasGen/AtlasGen.py -r ../../../resources -m RGBA -t tga

rm -rfv grids
mkdir grids
for i in ../../../resources/grids/*.txt; do
    cp -vf "${i}" grids/
done

for i in grids/*.txt; do
    ../../../tools/fix_grid.py "$i"
done

#valgrind --leak-check=full ./ponic
gdb ./ponic
