import os
import sys

def parent(i):
    return i/2
def left(i):
    return 2*i
def right(i):
    return 2*i + 1

def exchange(aList,i,j):
    tmp = aList[i]
    aList[i] = aList[j]
    aList[j] = tmp
    
def heapify(aList,i):
    if left(i) > len(aList):
        return
    
    print ("one",i,aList[i],left(i),right(i),len(aList))
    if len(aList) > right(i):
        if aList[right(i)] <= aList[left(i)]:
            if aList[i] > aList[right(i)]:
                print ("two",i,aList[i],aList[left(i)],aList[right(i)])
                exchange(aList,i,right(i))
                print ("three",i,aList[i],aList[left(i)],aList[right(i)])
                newI = right(i)
                print (aList)
                heapify(aList,newI)
                return
        else:
            if aList[i] > aList[left(i)]:
                print (i,aList[i],aList[left(i)],aList[right(i)])
                exchange(aList,i,left(i))
                print (i,aList[i],aList[left(i)],aList[right(i)])
                newI = left(i)
                print (aList)
                heapify(aList,newI)
                return
        
    print ("four",i,aList[i],left(i),right(i),len(aList))
    if (len(aList)-1) > left(i) and aList[left(i)] <= aList[i]:
       print (i,aList[i],aList[left(i)],aList[right(i)])
       exchange(aList,i,left(i))
       print (i,aList[i],aList[left(i)],aList[right(i)])
       newI = left(i)
       heapify(aList,newI)
    
    return    

def outHeap(aList):
    print ("pppppppppppppppppppp",aList[1])
    aList[1] = aList[len(aList)-1]
    aList.pop()
    print ("outHeap is ",aList)
    heapify(aList,1)
    return

aList = [99999]    
file = open('input.txt','r+')
for eachline in file:
    aString = eachline[0:len(eachline)-1]
    print (aString)
    aList.append((int)(aString))


file.close()
print (aList)
i = int((len(aList) + 1) / 2)
while i > 0:
    heapify(aList,i)
    i = i - 1
    print ("while    ",i,aList)

print ("outcome is ",aList)

j = len(aList)    
while j > 1:
    outHeap(aList)
    print ("outcome is ",aList)
    j = j - 1
    
print (aList)


