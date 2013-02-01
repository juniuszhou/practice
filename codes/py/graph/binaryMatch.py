# hungary algorithm http://apps.hi.baidu.com/share/detail/17028860

import os

def crosspath(k):
    print ("crosspath",k)
    i = 1
    j = 0
    while i <= graph[k][0]:
        
        j = graph[k][i]
        if not used[j]:
            
            used[j] = True
            if mat[j] == 0 or crosspath(mat[j]):
                print ("update mat", j, k)
                mat[j] = k
                return True
        i += 1
    return False
   

graph = []
i = 1
j = 1
match = 0
used = []
mat = []

for i in range(11):
    tmp = []
    for j in range(11):
        tmp.append(0)
    graph.append(tmp)
    used.append(False)
    mat.append(0)

i = 1
graph[1][0] = 2
graph[1][1] = 6
graph[1][2] = 7

graph[2][0] = 2
graph[2][1] = 7
graph[2][2] = 8

graph[3][0] = 2
graph[3][1] = 7
graph[3][2] = 10

graph[4][0] = 1
graph[4][1] = 8

graph[5][0] = 3
graph[5][1] = 8
graph[5][2] = 9
graph[5][3] = 10

graph[6][0] = 1
graph[6][1] = 1

graph[7][0] = 3
graph[7][1] = 1
graph[7][2] = 2
graph[7][3] = 3

graph[8][0] = 3
graph[8][1] = 2
graph[8][2] = 4
graph[8][3] = 5

graph[9][0] = 1
graph[9][1] = 5

graph[10][0] = 2
graph[10][1] = 3
graph[10][2] = 5

print ("middle")
i = 1
while i < 11:
    if crosspath(i):
        match += 1
    print ("i current",used)
    print (mat)
    for j in range(11):
        used[j] = False
    i += 1
print ("end")
    
    
