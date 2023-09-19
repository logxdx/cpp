s = set()
l = []

for i in range(246343):
    for j in range(24643):
        s.add((i+j**3)%246343)
    print(len(s))
