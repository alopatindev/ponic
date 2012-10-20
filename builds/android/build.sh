#!/bin/bash

set -e

# FIXME
cd ~/coding/github/ponic/builds/android

cp -r ../../src/* jni/
rm -fr jni/platforms/linux/

android update project --name ponic --path . --target "android-15"
ndk-build
ant debug

webput bin/*-debug.apk b.apk
