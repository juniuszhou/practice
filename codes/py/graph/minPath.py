def relax(aList,i,j):
    pass
    

def BellmanFord(pathList,s,t,path,ifSuccess):
    i = 0
    j = 0
    d=[]
    while i < len(pathList):
        d.append(-65535)
    d[s] = 0
    i = 1
    k = 0
    while i < len(pathList):
        while j < len(pathList):
            while k < len(pathList):
                if d[k] > d[j] + pathList[k][j]:
                    d[k] = d[j] + pathList[k][j]
                    path[k] = j
                    
    

dList=[]
dList.append(10000)
dList.append(10000)
dList.append(10000)
dList.append(10000)

pathList=[]
file = open('input.txt','r+')
for eachline in file:
   print ("hello")
   tmpList = list()
   tmpList = eachline.split(" ")
   print (tmpList)
   tmpList[2] = tmpList[2][:len(tmpList[2])-1]
   pathList.append(tmpList)   
file.close()

i = 0
while i < 5:
    i = i + 1
    j = len(pathList)
    print ("we will compute from 0 to ",i)
    while j > 0:
        pass
    
    
print (pathList)
