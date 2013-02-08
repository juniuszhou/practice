import os

def basicSort(aStr,saVec,maxChar):
    for i in range(257):
        tmpVec.append(0)
    i = 0
    
    while i < len(waVec):
        tmpVec[ord(inStr[waVec[i]])] += 1
        i = i + 1    
    
    i = 1
    while i < 257:
        tmpVec[i] = tmpVec[i - 1] + tmpVec[i]
        i = i + 1      
    pass

def doubling():
    i = 0
    saVec = []
    oriVec = []
    print (oriVec)
    while i < len(oriVec):
        saVec[oriVec[i]] += 1
        i = i + 1
    i = 1
    while i < len(saVec):
        saVec[i] += saVec[i-1]
        i = i + 1
    print (len(oriVec))
    i = len(oriVec) - 1
    while i >= 0:
        print (oriVec[i],chr(oriVec[i]),saVec[oriVec[i]])
        j = saVec[oriVec[i]] - 1
        #orderVec[saVec[oriVec[i]]] = i
        orderVec[i] = j
        i -= 1

def threeSort(inStr,waVec,wbVec):
    tmpVec = []
    tmpStr = inStr;
    tmpWV = []    

    print (inStr)
    for i in range(len(waVec)):
        tmpWV.append(0)    
    
    for i in range(len(waVec)):
        tmpWV[i] = inStr[waVec[i]]    
    
    for i in range(257):
        tmpVec.append(0)
    i = 0
    
    while i < len(waVec):
        tmpVec[ord(inStr[waVec[i]])] += 1
        i = i + 1    
    
    i = 1
    while i < 257:
        tmpVec[i] = tmpVec[i - 1] + tmpVec[i]
        i = i + 1        

    i = len(tmpWV) - 1
    
    while i >= 0:
        print (tmpVec[ord(tmpWV[i])])
        tmpVec[ord(tmpWV[i])] -= 1
        j = tmpVec[ord(tmpWV[i])]
        print (waVec[i], j)
        wbVec[j] = waVec[i]
        i = i - 1
    print (wbVec)

   
      
def dc3(inStr):
    oriLen = len(inStr)
    waVec = []
    wbVec = []
    
    indexVec = []
    rank12 = []
    rank12bak = []
    radix12 = []
    compVec = []
    inStr += '$'
    inStr += '$'
        

    for i in range(oriLen):
        if i % 3 == 0:            
            pass
        else:
            waVec.append(i)
    i = 0
    while i < len(waVec):
        wbVec.append(0)
        i = i + 1
        
    print (compVec)
    thirdStr = inStr[2:len(inStr)]
    print (thirdStr)
    threeSort(thirdStr,waVec,wbVec)

    secondStr = inStr[1:len(inStr)]
    threeSort(thirdStr,wbVec,waVec)
    threeSort(inStr,waVec,wbVec)   

    for i in range(len(wbVec)):
        print (inStr[wbVec[i]:wbVec[i]+3])

    p = 1
    i = wbVec[0]
    if i % 3 == 1:
        k = 0
    else:
        k = (oriLen + 1) / 3

oriString=""
oriString = input()
print (oriString)

dc3(oriString)

#doubling()

    
