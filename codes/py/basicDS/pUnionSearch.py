import os


def makeset(x):
    rank[x] = 1;
    p[x] = x;

def findset(x):
    px = x;
    while px != p[px]:
        px = p[px];
    return px

def findset_com(x):
    px = x
    while px != p[px]:
        p[px] = findset_com(p[px])
    return p[px]

def union(x,y):
    px = findset(x)
    py = findset(y)
    if px == py:
        return

    if rank[px] > rank[py]:
        p[py] = px
        rank[px] += rank[py]
    else:
        p[px] = py
        rank[py] += rank[px]
    
rank = []
p = []

for i in range(100):
    rank.append(0)
    p.append(0)

makeset(1)
makeset(2)
union(1,2)
print (findset(2))
makeset(3)
makeset(4)
union(3,4)
print (findset(3))
union(4,2)
print (findset(3))

