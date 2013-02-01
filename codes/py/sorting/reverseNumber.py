import os


def mergeSort(aList,begin,end):
    global count
    if begin >= end:
        return

    i = int((begin+end)/2)
    print (begin,end,i)
    mergeSort(aList,begin,i)
    mergeSort(aList,i+1,end)

    
    tmpList=list()
    b = begin
    e = i+1
    print (b,i,e,begin, end ,aList)
    while b <= i or e <= end:
        print ("into while ",b,i,e,begin, end ,aList)
        if e > end or ( b <= i and aList[b] < aList[e]):
            tmpList.append(aList[b])
            b += 1
            print ("b",b,tmpList)
        else:
            tmpList.append(aList[e])
            e += 1
            count = count + i - b + 1
            print ("e",count)
        print ("tmplist",tmpList)
        

    j = 0
    print ("second",begin, end ,aList)
    print ("second",begin, tmpList)
    while j < len(tmpList):
        aList[begin + j] = tmpList[j]
        j += 1
    print ("second",aList)

#global count
count = 0
aList=[]
aList.append(int(23))
aList.append(int(3))
aList.append(int(123))
aList.append(int(73))
aList.append(int(263))
aList.append(int(32))
aList.append(int(13))
aList.append(int(77))

print (aList)
mergeSort(aList,0,len(aList)-1)

#count is reserve number in a list
print (aList,count)
    
    
