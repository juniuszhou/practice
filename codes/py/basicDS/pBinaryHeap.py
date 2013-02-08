import os

def swim(heap,p):
    q = p>>1
    a = heap[q]
    print (q,a)
    while q > 0 and heap[p] < a:
        tmp = heap[p]
        heap[p] = heap[q]
        heap[q] = tmp
        p = q
        q = p>>1
    print ("after swim ",heap)
    
    

def insert(heap,p):
    global hs
    hs += 1
    heap[hs] = p
    print ("after insert ",hs, heap)
    swim(heap,hs)
    
heap = []
hs = 0
for i in range(30):
    heap.append(0)
    
for i in range(10):
    j = 2*i + 1
    insert(heap,j)
    
print (heap)

