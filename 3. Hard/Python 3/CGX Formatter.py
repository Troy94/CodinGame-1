import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

s = ''
n = int(input())
for i in range(n):
    s+=input()

print("\""+s+"\"", file=sys.stderr)

quo = 0
ind = 0
nl = 0
cur = 0
trimed = ''

for c in s:
    if c== '\'':
        quo = quo^1
    if quo==1 or (c!=' ' and c!='\t' and c!='\n'):
        trimed+=c

s = trimed

print("\""+s+"\"", file=sys.stderr)

for i in range(len(s)):
    c = s[i]

    if nl==1:
        print('\n', end="")
        print(' '*ind, end="")
        cur=ind
        nl=0

    if c!='\'' and quo==1:
        print(c, end="")
        cur+=1

    elif c=='(':
        if cur!=ind:
            print('\n', end="")
            print(' '*ind, end="")
            cur=ind
        print("(", end="")
        cur+=1
        ind+=4
        if i!=len(s)-1 and s[i+1]!=')':
            nl = 1

    elif c==';':
        print(c, end="")
        cur+=1
        nl=1

    elif c==')':
        print('\n', end="")
        ind-=4
        print(' '*ind, end="")
        cur=ind
        print(c, end="")
        cur+=1
        if i!=len(s)-1 and (s[i+1]!=';' and s[i+1]!=')'):
            nl = 1

    elif c=='\'':
        quo^=1
        print(c, end="")
        cur+=1

    else:
        print(c, end="")
        cur+=1
