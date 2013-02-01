import os

def dfs(selectVec,stoneNumber):
    if SG[stoneNumber] != -1:
        return
    visited=[]
    i = 0
    while i < stoneNumber:
        visited.append(False)
        i = i + 1
    print (selectVec)
    print ("first")
    print (SG)
    i = 0
    while i < stoneNumber:
        tmp = stoneNumber - selectVec[i]
        if tmp >= 0:
            if SG[i] == -1:
                dfs(selectVec,tmp)
            visited[SG[i]] = True
        i = i + 1
    print (selectVec)
    print ("second")
    print (SG)
    i = 0
    while i < stoneNumber:
        if not visited[i]:
            SG[stoneNumber] = i
            return
    i = i + 1
    print (selectVec)
    print ("third")
    print (SG)   

selectVec=[]
selectVec.append(int(1))
selectVec.append(int(2))
selectVec.append(int(3))

stoneNumber = 10
i = 0
SG = []
while i <= stoneNumber:
    SG.append(-1)
    i = i + 1
SG[0] = 0
print (selectVec)
print (SG)
dfs(selectVec,stoneNumber)
