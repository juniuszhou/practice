import sys
import os

# 0 uninitilized, 1 left, 2 up, 3 diagnoal
class nodeType:
    direction = 0
    value = 0
    
stringOne = "qwegsdgreewredgh"
stringTwo = "rehtrehe"

lengthOne = len(stringOne)
legnthTwo = len(stringTwo)

newNode = nodeType()
newNode.direction = 7

aList = []
i = 0
j = 0
while i <= lengthOne:
    tmpList = list()
    j = 0
    while j <= legnthTwo:
        tmpNode = nodeType()
        tmpList.append(tmpNode)
        j = j + 1
    aList.append(tmpList)
    i = i + 1

i = 1
j = 1
while i <= lengthOne:
    j = 1
    while j <= legnthTwo:
        print (stringOne[i-1],stringTwo[j-1])
        print (aList[i][j-1].value,aList[i-1][j].value)
        if stringOne[i-1] == stringTwo[j-1]:
            aList[i][j].direction = 3
            aList[i][j].value = aList[i-1][j-1].value + 1
        elif aList[i][j-1].value >= aList[i-1][j].value:
            aList[i][j].direction = 2
            aList[i][j].value = aList[i][j-1].value
        else:
            aList[i][j].direction = 1
            aList[i][j].value = aList[i-1][j].value
        j = j + 1
    i = i + 1

print ("well done",aList[i-1][j-1].value)


        
