n=int(raw_input())
a= sorted([int(raw_input()) for i in range(n)])
d = 10000000
for i in range(n-1):
    d = min(d,a[i+1]-a[i])
print (d)