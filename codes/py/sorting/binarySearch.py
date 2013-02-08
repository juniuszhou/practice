def binarySearch(aList,low,high,value):
    if low >= high:
        return -1
    medium = int((low+high)/2)
    if value == aList[medium]:
        return medium
    elif value > aList[medium]:
        return binarySearch(aList,medium,high,value)
    else:
        return binarySearch(aList,low,medium,value)
    
    
    
aList=[]
file = open('input.txt','r+')
for eachline in file:
    aString = eachline[0:len(eachline)-1]
    aList.append(int(aString))
aList.sort()
print (aList)

k = binarySearch(aList,0,len(aList)-1,43)
print (k)

file.close()

