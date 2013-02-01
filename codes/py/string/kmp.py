import sys
# basic data type
myString = 'Hello World ababababcaababababca'
matchString = 'ababababca'
length = len(matchString)
aList=[]
i = 0
while i<length:
     aList.append(0)
     i = i + 1     
else:
     print ('while loop is over')

i = 1
while i < length:
     lastValue = aList[i-1]
     if matchString[i] == matchString[lastValue]:
          aList[i] = lastValue + 1
     i = i + 1
else:
     print (aList)
     print (matchString)

i = 0
while i < len(myString) - length + 1:
     j = 0
     while j < length:
          if myString[i + j] == matchString[j]:
               j = j + 1
          else:
               i = i + aList[j]
               break
     else:
          print ("")          
     if j == length:
          print ("matched position is")
          print (i,i+length)
          strMatched = myString[i:i+length]
          print (strMatched)
          i = i + length
     else:
          i = i + 1
     print (i,j)

     
 












