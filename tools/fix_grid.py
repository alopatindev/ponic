#!/usr/bin/env python2

import sys

if len(sys.argv) < 2:
    print '%s path/to/level.txt'
    sys.exit(1)

filename = sys.argv[1]

f = open(filename, 'r')
lines = f.readlines()
f.close()

rows = len(lines)
cols = len(lines[0]) - 1

for i in xrange(1, len(lines)):
    print len(lines[i]), cols
    if len(lines[i]) - 1 != cols:
        print 'Error: wrong number of characters in %s:%d' % (filename, i)
        sys.exit(2)

lines.insert(0, '%d %d\n' % (cols, rows))

f = open(filename, 'w')
f.writelines(lines)
f.close()
