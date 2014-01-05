#!/usr/bin/env python2

import sys

if len(sys.argv) < 2:
    print '%s path/to/level.txt'
    sys.exit(1)

f = open(sys.argv[1], 'r')
lines = f.readlines()
f.close()

rows = len(lines) - 1
cols = len(lines[1]) - 1

lines[0] = '%d %d\n' % (cols, rows)
print lines

f = open(sys.argv[1], 'w')
f.writelines(lines)
f.close()
