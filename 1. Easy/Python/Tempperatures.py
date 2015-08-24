n = input()
a = sorted([int(i) for i in raw_input().split()], reverse=True)
if len(a)==0:
    print("0")
else:
    print min(a, key=lambda x:abs(x))