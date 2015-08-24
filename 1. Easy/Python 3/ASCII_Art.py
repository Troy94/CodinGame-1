import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

L = int(input())
H = int(input())
T = list(input())
for i in range(len(T)):
    if T[i].isalpha():
        T[i] = T[i].upper()
    else:
        T[i] = '['
set = [ input() for i in range(H)]
T = ''.join(T)
for i in range(H):
    for c in T:
        n = (ord(c) - ord('A'))*L
        print(set[i][n:n+L], end="")
    print("")
