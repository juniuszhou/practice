import os
import sys

def exchange(i,j):
    tmp = i
    i = j
    j = tmp


i = 8;
j = 9;
exchange(i,j)
print (i,j)
exit()

file = open('input.txt','r+')
for eachline in file:
    aString = eachline[0:len(eachline)-1]
    print (aString)

file.write("at the end of file\n")
file.close()

file = open('input.txt','r+')
for eachline in file:
    aString = eachline[0:len(eachline)-1]
    print (aString)
