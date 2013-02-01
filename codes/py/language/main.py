#!/usr/bin/python
import sys
import os

def catalan( i):
   if i<2:
      return 1
   print ("calan",i)
   j = i
   k = 0
   sum = 0
   while j > 0:
      j = j - 1
      sum = sum + catalan(k) * catalan(j)
      k = k + 1
   return sum


print ("hello world")

k = catalan(10)
print (k)

