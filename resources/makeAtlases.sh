#!/bin/sh

set -e
cd ../bin
../tools/AtlasGen/AtlasGen.py -r ../resources -m RGBA -t tga
