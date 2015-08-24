import sys
import math

L = int(raw_input())
H = int(raw_input())
T = list(raw_input())
for i in range(len(T)):
    if T[i].isalpha():
        T[i] = T[i].upper()
    else:
        T[i] = '['
T = ''.join(T)
set = [ raw_input() for i in range(H)]
ans=""
for i in range(H):
    for c in T:
        n = (ord(c) - ord('A'))*L
        ans+=set[i][n:n+L]
    ans+="\n"
print ans
