import sys
import math
lx, ly, tx, ty = [int(i) for i in input().split()]
while 1:
    remainingTurns = int(input())
    dir = ""
    if ly<ty:
        dir+='N'
        ty-=1
    elif ly>ty:
        dir+='S'
        ty+=1
        
    if lx<tx:
        dir+='W'
        tx-=1
    elif lx>tx:
        dir+='E'
        tx+=1       
    print (dir)
