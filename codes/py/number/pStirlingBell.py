import os

#S(n+1,k) = S(n,k-1) + nS(n,k)
def stirling(a,b):
    if a == 1 and b == 1:
        return 1
    if b == 0:
        return 0
    if a == 0:
        return 0
    return stirling(a-1,b-1) + (a-1)*stirling(a-1,b)

#S(n,k) = S(n-1,k-1) - kS(n-1,k)
def stirling2(a,b):
   
    if a == b:
        return 1
    if b == 1:
        return 1
    if a < b or b == 0:
       return 0    
    
    return stirling2(a-1,b-1) + b*stirling2(a-1,b)

# bell B(n+1) = sum(0,n)C(n,k)B(k)
# B(n) = Sum(1,n) S(n,k).

def jiechen(a,b):
    if a == b:
        return 1
    if b == 0:
        return 1 
    aj = 1
    bj = 1
    abj = 1
    i = 1
    while i <= a:
        aj *= i
        i = i + 1
    i = 1
    while i <= b:
        bj *= i
        i = i + 1
    i = 1
    while i <= a-b:
        abj *= i
        i = i + 1
    return int(aj / bj / abj)
        
def bell(a):
    if a < 2:
        return 1
    i = 0
    count = 0
    while i < a:
        count += jiechen(a-1,i)*bell(i)
        i += 1
    return count

k = bell(5)
print (k)
