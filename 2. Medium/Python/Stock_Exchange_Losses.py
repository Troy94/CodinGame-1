n = int(raw_input())
a = [ int(i) for i in raw_input().split()]
cmax=a[0]
ans =0
for i in a:
    ans = min(ans,i-cmax)
    cmax=max(cmax,i)
