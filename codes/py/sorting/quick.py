#quick sorting

def quickSort(aList,i,j):
    if i >= j:
        return
    elif i == j - 1:
        tmpMix = 0
        tmpMax = 0
        tmpMix = min(aList[i],aList[j])
        tmpMax = max(aList[i],aList[j])
        aList[i] = tmpMix
        aList[j] = tmpMax
        return
    else:
        print ("quickSort is called",i,j,"current list",aList)
        factor = aList[i]
        begin = i + 1
        end = j
        position = i
        print (i,j,position,factor,aList[begin])
        print (aList)
        while begin <= end:
            while int(factor) < int(aList[end]) and begin <= end:
                end = end - 1
            else:
                if  begin <= end:
                    aList[position] = aList[end]
                    position = end
                    end = end - 1
                    print ("after end",aList,"factor",factor)

                
            while int(factor) > int(aList[begin]) and begin <= end:
                begin = begin + 1                
                print ("while",factor,begin,end,aList[begin])
            else:
                if begin <= end:
                    print ("else")
                    aList[position] = aList[begin]
                    position = begin
                    begin = begin + 1
                    print ("after begin",aList)            
            
            if begin > end:
                break           
            
            print (aList)
        aList[position] = factor
        print (i,j,position)
        print (aList)
        newEnd = 0
        newBegin = 0
        if position > 1:
            newEnd = position - 1
        if position < j:
            newBegin = position + 1
        print ("will call",i,newEnd,position,j,newBegin)
        quickSort(aList,i,newEnd)
        quickSort(aList,newBegin,j)

i = 0
aList = []
aList.append(6)
aList.append(10)
aList.append(13)
aList.append(5)
aList.append(8)
aList.append(3)
aList.append(2)
aList.append(11)
aList.append(56)
aList.append(6)
aList.append(18)
aList.append(26)
aList.append(33)
print (aList)

length = len(aList)
quickSort(aList,0,length-1)
print (aList)
