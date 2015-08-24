import sys
import math

def bits(c):
    b = []
    for i in range(7):
        b.append(c%2)
        c//=2
    return b[::-1]

m = raw_input()
bit = []
for c in m:
    bit.extend(bits(ord(c)))
first = True
c = 2
ans=""
for i in bit:
    if i==c:
        ans+="0"
    else:
        if not first:
            ans+=" "
        if i==1:
            c = 1
            ans+="0 0"
        else:
            c = 0
            ans+="00 0"
    first = False

print ans