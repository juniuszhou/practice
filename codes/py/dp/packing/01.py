import os

def zeroOnePack(cost, weight,volumnList):
    i = len(volumnList)
    while i >= 0:
        print (i,i-cost)
        if ( i - cost ) > 0:
            if volumnList[i-1] < ( volumnList[i-cost-1] + weight ):
                volumnList[i-1] = volumnList[i-cost-1] + weight
                
        i = i - 1
        print (volumnList)
        
#the index of volumnList represents the current cost
#the value of volumnList represents the max weight until
        
def completePack(cost,weight,volumnList):
    i = 0
    while i <= len(volumnList):
        print (i,i-cost)
        if ( i - cost ) > 0:
            if volumnList[i-1] < ( volumnList[i-cost-1] + weight ):
                volumnList[i-1] = volumnList[i-cost-1] + weight
        i = i + 1

def multiplyPack(cost,weight,amount,volumnList):
    if cost*amount >= len(volumnList):
        CompletePack(cost,weight,volumnList)
        return
    k = 1
    while k < amount:
        zeroOnePack(cost,weight,volumnList)
        amount=amount-k
        k = k + k
    zeroOnePack(amount*cost,amout*weight)
        

    
weightList=[]
costList=[]

packColumn=19

i = 0
volumnList=[]
while i < packColumn:
    volumnList.append(int(0))
    i = i + 1
    
volumnList.append(int(0))

weightList.append(int(1))
costList.append(int(3))
weightList.append(int(2))
costList.append(int(5))
weightList.append(int(3))
costList.append(int(7))
weightList.append(int(4))
costList.append(int(9))
weightList.append(int(5))
costList.append(int(10))

i = 0
while i < len(costList):
    print ("we will call ",costList[i],weightList[i],volumnList)
    zeroOnePack(costList[i],weightList[i],volumnList)
    i = i + 1
    
print (len(volumnList),volumnList)
