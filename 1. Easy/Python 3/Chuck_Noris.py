import sys
import math

def bits(c):
    b = []
    for i in range(7):
        b.append(c%2)
        c//=2
    return b[::-1]

m = input()
bit = []
for c in m:
    bit.extend(bits(ord(c)))
first = True
c = 2
for i in bit:
    if i==c:
        print("0",end="")
    else:
        if not first:
            print(" ", end="")
        if i==1:
            c = 1
            print("0 0",end="")
        else:
            c = 0
            print("00 0",end="")
    first = False
