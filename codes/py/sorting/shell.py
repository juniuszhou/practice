import os

def shellSorting(aList):
    
    distance = int(len(aList)/2)

    while distance > 0:
        i = distance + 1
        while i < len(aList):
            t1 = aList[i]
            j = i - distance
            while j > 0:
                t2 = j + distance
                print ("compare",aList[j],aList[t2], distance, j, t2)
                if int(aList[j]) <= int(aList[t2]):
                    j = 0
                else:
                    print ("exchange",aList[j],aList[t2])
                    t3 = aList[j]
                    aList[j] = aList[t2]
                    aList[t2] = t3
                    j = j - distance
            i = i + 1
        distance = int(distance/2)
        print(aList)


aList=[]
aList.append(0)
aList.append(45)
aList.append(6)
aList.append(123)
aList.append(87)
aList.append(94)
aList.append(33)
aList.append(65)
aList.append(111)
print(aList)
shellSorting(aList)
print(aList)



            
