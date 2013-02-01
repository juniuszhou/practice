#!/usr/bin/python
import sys
import os 

#h(n)= h(0)*h(n-1) + h(1)*h(n-2) + ... + h(n-1)h(0)
#h(n)=c(2n,n)/(n+1)
def catalan( i):
   if i<2:
      return 1
   j = i
   k = 0
   sum = 0
   while j > 0:
      j = j - 1
      sum = sum + catalan(k) * catalan(j)
      k = k + 1
   return sum

print ("hello world")
k = 0
while k < 8:
    r = catalan(k)
    print ("catlan ",k," is ",r)
    k = k + 1
