#!/bin/bash

set -e

_JAVA_OPTIONS='-Dawt.useSystemAAFontSettings=lcd -Xms256m -Xmx512m -XX:MaxHeapSize=256m'
ANDROID_NDK='/opt/android-ndk/'
NDK_ROOT='/opt/android-ndk'

BUILD_RESOURCES=1
RES_DIR='res/raw'

BUILD_DIR=$(dirname ${BASH_SOURCE[0]})
cd "${BUILD_DIR}"

cd jni
ln -sf ../../../src/* .
cd ..
rm -f src
ln -sf jni/engine/platforms/android/java src

if [[ $BUILD_RESOURCES == 1 ]]; then
    rm -fr $RES_DIR
    mkdir -p $RES_DIR
    cp -rv jni/engine/platforms/android/shaders $RES_DIR/shaders
    cd $RES_DIR
    ../../../../tools/AtlasGen/AtlasGen.py -r ../../../../resources \
        -m RGBA -t tga
    7z a res.zip atlases/ shaders/
    cd ../..
fi

android update project --name ponic --path . --target "android-15"
ndk-build V=1 -j4
ant debug

webput bin/*-debug.apk b.apk
