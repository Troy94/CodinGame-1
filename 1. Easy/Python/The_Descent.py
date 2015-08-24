import sys
import math

while 1:
    sX, sY = [int(i) for i in raw_input().split()]
    m = [int(raw_input()) for i in xrange(8)]
    if m.index(max(m)) == sX:
        print "FIRE"
    else :
        print "HOLD"
