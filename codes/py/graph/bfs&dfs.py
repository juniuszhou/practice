import io
#function for breadth first search, aList is a link matrix
def bfs(aList):
    outList = []    
    outList.append(0)
    while len(outList) > 0:
        j = 0
        i = outList.pop()
        print ("now output is ",i)        
        while j < len(aList):            
            if aList[i][j] > 0 or aList[j][i] > 0:
                print (j)
                outList.insert(0,j)
                aList[i][j] = 0
                aList[j][i] = 0
            j = j + 1                
    print ("")

def dfs(aList):
    order = 0
    orderlist = []
    outList=[]
    print ("now output is ",0)
    while len(pointList) > 0:
        i = pointList.pop()
        order = order + 1
        orderlist.append(i)
        
        outList.append(i)
        print ("now output is ",i)
        while len(outList) > 0:
            j = 0
            while j < len(aList):
                if aList[i][j] > 0:
                    outList.append(j)
                    order = order + 1
                    orderlist.append(j)
                    pointList.remove(j)
                    aList[i][j] = 0
                    break
                j = j + 1
            if j >= len(aList):
                outList.pop()
    return orderlist

def strongConnectComponent(aList):
    pass
    
        
linkTable=[[]]
i = 0
j = 0

while i < 8:
    j = 0
    tmpList=list()
    linkTable.append(tmpList)
    while j < 8:
        tmpList.append(0)        
        j = j + 1
    i = i + 1

pointList=[]

file = open('input.txt','r+')
for eachline in file:
    points = eachline.split(" ",)
    print (points)
    if int(points[0]) >= 0:
        linkTable[int(i)][int(j)] = 1
        if int(i) not in pointList:
            pointList.append(int(i))
        if int(j) not in pointList:
            pointList.append(int(j))
            
print ("well done")
