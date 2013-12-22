#!/bin/sh

BUILD_DIR=$(dirname ${BASH_SOURCE[0]})
cd "${BUILD_DIR}"
rm -fvr CMakeCache.txt CMakeFiles cmake_install.cmake Makefile bin ../../src/all.h
