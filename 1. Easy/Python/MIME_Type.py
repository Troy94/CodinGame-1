hash = {}
N = int(raw_input())
Q = int(raw_input()) 
for i in range(N):
    ext, type = raw_input().split()
    hash[ext.lower()] = type
for i in range(Q):
    file = raw_input()
    if '.' in file:
        file = file.split('.')[-1]
        print(hash.get(file.lower(),"UNKNOWN"))
    else:
        print("UNKNOWN")
