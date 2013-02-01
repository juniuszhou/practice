import os

def generateGrayCode(length):
    i = 0
    while i < (1 << length):
        j = i ^ (i >> 1)
        print ('%x' % (j))
        i = i + 1

generateGrayCode(7)
    

