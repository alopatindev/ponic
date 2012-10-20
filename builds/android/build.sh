#!/bin/bash

set -e

_JAVA_OPTIONS='-Dawt.useSystemAAFontSettings=lcd -Xms256m -Xmx512m -XX:MaxHeapSize=256m'
ANDROID_NDK='/opt/android-ndk/'
NDK_ROOT='/opt/android-ndk'

# FIXME
cd ~/coding/github/ponic/builds/android

#RES_DIR=res/raw
RES_DIR=assets
rm -fr $RES_DIR

cp -r ../../src/* jni/
rm -fr jni/platforms/linux/

mkdir -p $RES_DIR
mv jni/engine/shaders $RES_DIR/shaders
cd $RES_DIR
../../../tools/AtlasGen/AtlasGen.py -r ../../../resources -m RGBA -t tga
cd ..

android update project --name ponic --path . --target "android-15"
ndk-build V=1 -j4
ant debug

webput bin/*-debug.apk b.apk
