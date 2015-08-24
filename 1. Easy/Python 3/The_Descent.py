while 1:
    sX, sY = [int(i) for i in input().split()]
    m = [int(input()) for i in range(8)]
    if m.index(max(m)) == sX:
        print ("FIRE")
    else :
        print ("HOLD")
