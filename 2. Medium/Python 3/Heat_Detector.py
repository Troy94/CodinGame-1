w,h = [int(i) for i in input().split()]
n = int(input())
x,y = [int(i) for i in input().split()]
lx,hx = [0,w-1]
ly,hy = [0,h-1]

while 1:
    dir = input()
    if dir == "U":
        hy = y-1
    elif dir == "UR":
        hy = y-1
        lx = x+1
    elif dir == "R":
        lx = x+1
    elif dir == "DR":
        ly = y+1
        lx = x+1
    elif dir == "D":
        ly = y+1
    elif dir == "DL":
        ly = y+1
        hx = x-1
    elif dir == "L":
        hx = x-1
    elif dir == "UL":
        hy = y-1
        hx = x-1
    x = (lx+hx)//2
    y = (ly+hy)//2
    print(x,y)