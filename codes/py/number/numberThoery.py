def gcd(a,b):
    c = a % b
    if c == 0:
        return b
    else:
        return gcd(b,c)

def extensiveGcd(a,b,aList):
    if b == 0:
        aList[0] = a
        aList[1] = 1
        aList[2] = 0
    else:
        extensiveGcd(b,a % b,aList)
        x = aList[0]
        y = aList[1]
        z = aList[2]

        aList[0] = x
        aList[1] = z
        aList[2] = y - z * (int( a / b))
    return

#求di的aList次方对n 的模       
def Mi(di,aList,n):    
    i = 0
    outcome = 1
    while i < len(aList):
        if aList[i]>0:
            print ("if  ",outcome,di,n)
            outcome = ( outcome * di ) % n
        print (" di before ",outcome,di,n)   
        di =  ( di * di ) % n
        print (" di after ",outcome,di,n)  
        i = i + 1
        
    return outcome

def sameMode(a,b,n):
    c = gcd(a,n)
    if c % b == 0:
        pass
        
    else:
        return -1

def china(aList,bList,ret):
    i = 0
    a = 0
    j = 1
    tmpList=[]
    tmpList.append(int(0))
    tmpList.append(int(0))
    tmpList.append(int(0))
    
    while i < len(aList):
        j = j * aList[i]
        i = i + 1
    i = 0
    k = 1
    while i < len(aList):
        k = int(j / aList[i])
        print (k,tmpList)
        extensiveGcd(k,aList[i],tmpList)
        print (k, bList[i], tmpList)
        a = ( a + tmpList[1] * k  * bList[i] ) % j
        print (a,tmpList[1],k,bList[i],j)
        i = i + 1
    return 1
    
def isPrimeNumber(k,a):
    print ("into this method")
    if k == 0:
        return 0
    print ("into this method")
    b = 0
    c = k - 1
    alist = []
    print ("into this method")
    while c > 1:
        tmp = c % 2
        c = int(c / 2)
        alist.insert(0,tmp)
    alist.insert(0,1)
    alist.reverse()
    print ("alist is",alist)
    b = Mi(a,alist,k)
    print ("b is ",b)
    if b == 1:
        return 1
    return 0

def miller_rabin(k,a):
    b = k - 1
    i = 0
    while b%2 == 0:
        i = i + 1
        b = b / 2
    c = b
    while c > 1:
        tmp = c % 2
        c = int(c / 2)
        alist.insert(0,tmp)
    alist.insert(0,1)
    alist.reverse()

    d = Mi(a,alist,k)
    
aa=37
bb=6
if isPrimeNumber(aa,bb)==1:
    print ("haha I found out prime")

c = 0    
aList=[]
aList.append(int(3))
aList.append(int(5))
aList.append(int(7))

bList=[]
bList.append(int(2))
bList.append(int(3))
bList.append(int(2))

dList=[]
dList.append(int(2))
dList.append(int(3))
dList.append(int(2))

china(aList,bList,c)
print (c)

cList=[]
cList.append(int(1))
cList.append(int(1))
cList.append(int(1))
a = 99
b = 42
extensiveGcd(99,42,cList)
print (cList)

