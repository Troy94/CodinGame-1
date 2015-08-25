a = [int(raw_input())]
it = int(raw_input())

for i in range(it-1):
    f = 0;
    c = a[0]
    b = []
    for x in a:
        if x==c:
            f+=1
        else:
            b.extend([f,c])
            f = 1
            c = x
    b.extend([f,c])
    a = b
    
print ' '.join(map(str, a))
            