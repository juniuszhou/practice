import os

class twoDimPoint:
    def   __init__(self):
        self.x = 0
        self.y = 0

class threeDimPoint:
    def   __init__(self):
        self.x = 0
        self.y = 0
        self.z = 0
        
def MAX(i,j):
    if i > j:
        return i
    else:
        return j

def MIN(i,j):
    if i > j:
        return j
    else:
        return i
    
def cos(i,j):
    return dotProduct(i,j) / (dotProduct(i,i) * dotProduct(j,j))

def crossProduct(i,j):
    pass

def dotProduct(i,j):
    return i.x * j.x + i.y * j.y + i.z * j.z
          
    
def direction(p,pBegin,pEnd):
    tmp1 = twoDimPoint()
    tmp1.x = pBegin.x - p.x
    tmp1.y = pBegin.y - p.y

    tmp2 = twoDimPoint()
    tmp2.x = pEnd.x - p.x
    tmp2.y = pEnd.y - p.y

    return tmp1.x * tmp2.y - tmp2.x * tmp1.y

def onsegment(p,pBegin,pEnd):
    if MIN(pBegin.x,pEnd.x) <= p.x and
    p.x <= MAX(pBegin.x,pEnd.x) and
    MIN(pBegin.y,pEnd.y) <= p.y and
    p.y <= MAX(pBegin.y,pEnd.y):
        return true
    else:
        return false
#we can use matrix to store relationship for any two segment.
    
def anySegmentIntersect():
    pass
a = twoDimPoint()
b = twoDimPoint()

    
