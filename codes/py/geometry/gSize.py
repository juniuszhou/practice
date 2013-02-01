import os
import math

class twoDimPoint:
    def   __init__(self):
        self.x = 0
        self.y = 0
        
def sizeOfTriangle(a,b,c):
    t1 = math.sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y))
    t2 = math.sqrt((a.x-c.x)*(a.x-c.x) + (a.y-c.y)*(a.y-c.y))
    t3 = math.sqrt((c.x-b.x)*(c.x-b.x) + (c.y-b.y)*(c.y-b.y))
    t4 = (t1+t2+t3)/2
    result = math.sqrt(t4*(t4-t1)*(t4-t2)*(t4-t3))
    return result

#concept behind the algorithm. computing all size of every
#segment and original point. you can get a triangle's size.
#you can find out the relationship of polygon area and all triangles

def sizeOfPolygonarea(pList):
    i = 0
    size = 0
    while i < len(pList):
        j = i + 1;
        if j == len(pList):
            j = 0
        size = size + pList[i].x * pList[j].y
        size = size - pList[i].y * pList[j].x
    size = size / 2
    return size
        
def angle(a,b):
    t1 = atan2(a.y,a.x)
    t2 = atan2(b.y,b.x)
    t3 = t2 - t1
    return t3
    
def distance(a,b):
    t1 = math.sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y))
    return t1

#pay attention to float calculation
#here we assume all data are integers
def pointOnSegment(a,begin,end):
    t1 = a.x - begin.x
    t2 = a.y - begin.y
    t3 = a.x - end.x
    t4 = a.y - end.y
    t5 = t1 * t4 - t2 * t3
    
    if t5 != 0:
        return 0
    if a.x > begin.x and a.x < end.x and a.y > begin.y and a.y < end.y:
        return 1
    return 0

#ray started from a to judge if a is in Polygon
#if cross points is even then out, 
def pointInPolygon(a,pList):
    i = 0
    counter = 0
    p1 = pList[0]
    while i < len(pList):
        i = i + 1
        p2 = pList[i]
        if p.y > p1.y and p.y > p2.y:
            next
        if p.y < p1.y and p.y < p2.y:
            next
        if p.x > p1.x and p.x > p2.x:
            next
        #it need to draw a triangle to understand it
        t1 = (p.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x
        if p1.x==p2.x or p.x < t1:
            counter = counter + 1
        p1 = p2
    if count % 2 == 0:
        return False
    else:
        return True

p1 = twoDimPoint()
p2 = twoDimPoint()
p3 = twoDimPoint()
p1.x = 2
p1.y = 6
p2.x = 1
p2.y = 4
p3.x = 3
p3.y = 10

result = pointOnSegment(p1,p2,p3)
print (result)
