hash = {}
N = int(input())
Q = int(input()) 
for i in range(N):
    ext, type = input().split()
    hash[ext.lower()] = type
for i in range(Q):
    file = input()
    if '.' in file:
        file = file.split('.')[-1]
        print(hash.get(file.lower(),"UNKNOWN"))
    else:
        print("UNKNOWN")
