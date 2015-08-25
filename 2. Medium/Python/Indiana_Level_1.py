dict = {"LEFT":{1:[0,1], 2:[1,0], 5:[0,1], 6:[1,0], 8:[0,1], 9:[0,1], 13:[0,1]}, \
        "RIGHT" :{1:[0,1], 2:[-1,0], 4:[0,1], 6:[-1,0], 7:[0,1], 8:[0,1], 12:[0,1]}, \
        "TOP"  :{1:[0,1], 3:[0,1], 4:[-1,0], 5:[1,0], 7:[0,1], 9:[0,1], 10:[-1,0], 11:[1,0]} };
    
W, H = [int(i) for i in raw_input().split()]
a =[]
for i in range(H):
    a.append( [int(i) for i in raw_input().split()])
ex = int(raw_input())

while 1:
    x,y,pos = raw_input().split()
    x,y = [int(x),int(y)]
    x,y = [x+dict[pos][a[y][x]][0], y+dict[pos][a[y][x]][1]]
    print x,y
    
    
