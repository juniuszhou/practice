import os

def floodfill(x):
    if mark[x] == 0:
        return
    print ("")
    px = int(x / 10)
    py = x % 10
    i = 0
    j = 0
    
    mark[x] = 0
    print (px," ",py," @ ")
    if x + 10 < 100:
        floodfill(x+10)
    if x - 10 >= 0:
        floodfill(x-10)
    if x + 1 < 100:
        floodfill(x+1)
    if x - 1 >= 0:
        floodfill(x-1)
    


mark = []
i = 0
j = 0
while i < 10:
    j = 0
    while j < 10:
        mark.append(0)
        j += 1
    i += 1

i = 3
while i < 100:
    mark[i] = 1
    i += 10

floodfill(13)

print (mark)



