import sys
import os
#input and output
stringName = input("please input: ")
print (stringName)

#new data generate factory
#int(), long(), float(), complex()
#str(), unicode(), basestring()
#list(), tuple()type() dict()
#bool()set(), frozenset()
#object()classmethod()
#staticmethod()super()
#property()file()


#
aChar = len(stringName)
print ("length is",aChar)
j = aChar * 2
i = 0
while i < j:
    print (stringName[i])
    i = i + 1
else:
    pass

#file operation and exceptions
try:
     filename = raw_input('Enter file name: ')
     fobj = open(filename, 'r')
     for eachLine in fobj:
         print eachLine,
     fobj.close()
  except IOError, e:
       print 'file open error:', e












