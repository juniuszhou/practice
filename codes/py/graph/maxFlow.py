#import os

def initFlow():
    pass

def pushFlow(u,v):    
    tmpValue = leftFlow[u]
    if leftFlow[u] > weight[u][v]:
        tmpValue = weight[u][v]
    residual[u][v] += tmpValue
    residual[v][u] = -tmpValue
    leftFlow[u] -= tmpValue
    leftFlow[v] += tmpValue
    print ("left flow is ",leftFlow)
    print (residual)
    
def relabelFlow(u):
    minheight = 7
    for i in range(6):
        if weight[u][i] > residual[u][i] and height[i] < minheight:
            minheight = height[i]
            print ("height is ",height[i])
    if minheight == 7:
        return False

    height[u] = minheight + 1
    for i in range(6):
        if leftFlow[u] == 0:
            break
        if height[i] == minheight and weight[u][i] > residual[u][i]:
            pushFlow(u,i);
    return True    
        
    
weight = []
residual = []
for i in range(6):
    tmp = []
    for j in range(6):
        tmp.append(0)
    weight.append(tmp)
for i in range(6):
    tmp = []
    for j in range(6):
        tmp.append(0)
    residual.append(tmp)
    
leftFlow = []
height = []

for i in range(6):
    leftFlow.append(0)
    height.append(0)
    
weight[0][1] = 16
weight[0][2] = 13
weight[1][2] = 10
weight[1][3] = 12
weight[2][1] = 4
weight[2][4] = 14
weight[3][2] = 9
weight[3][5] = 20
weight[4][3] = 7
weight[4][5] = 4



source = 0
dest = 5

height[source] = 6

for i in range(6):
    if weight[0][i] > 0:
        leftFlow[0] -= weight[0][i]
        leftFlow[i] = weight[0][i]
        residual[0][i] = weight[0][i]
        residual[i][0] = -weight[0][i]
print (weight)
print (residual)
push = True
relabel = True

while relabel:
    push = False
    relabel = False
    print ("i ma into")
    i = 1
    while i < 5:
        if leftFlow[i] > 0:
            tmpbool = relabelFlow(i)
            print ("returned is ", tmpbool, "i is ", i)
            relabel = tmpbool or relabel
        i += 1
    print ("relabel is ", relabel)
            
   
    
print (weight)
print (leftFlow)

