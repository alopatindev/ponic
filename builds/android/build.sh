#!/bin/bash

android update project --name ponic --path . --target "android-15"
ndk-build
ant debug
webput bin/*-debug.apk b.apk
