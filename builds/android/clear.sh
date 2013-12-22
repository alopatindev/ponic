#!/bin/sh
# vim: textwidth=0

BUILD_DIR=$(dirname ${BASH_SOURCE[0]})
cd "${BUILD_DIR}"

rm -fvr build.xml libs proguard-project.txt bin gen local.properties project.properties obj jni/{game,engine} res/raw assets src
