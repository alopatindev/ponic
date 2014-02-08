#!/usr/bin/env python2

import sys
import os

if len(sys.argv) < 3:
    print '%s path/to/animations.txt path/to/textures/'
    sys.exit(1)

filename = sys.argv[1]
textures_dir = sys.argv[2]

def calculate_frames(group, name):
    files = os.listdir(os.path.join(textures_dir, group))
    result = 0
    for i in files:
        fn, ext = os.path.splitext(i)
        if ext == '.png' and fn[:len(name)] == name:
            result += 1
    return result

f = open(filename, 'r')
lines = f.readlines()
f.close()

for i in xrange(len(lines)):
    lines[i] = lines[i].replace('\r', '').replace('\n', '')
    group, name, fps = lines[i].split(' ')
    frames = calculate_frames(group, name)
    lines[i] = '%s %s %s %d\n' % (group, name, fps, frames)

f = open(filename, 'w')
f.writelines(lines)
f.close()
