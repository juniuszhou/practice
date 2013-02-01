import os

class Node():
    value = 0
    prev = None
    nextN = None

def link(a,b):
    if a.value > b.value:
        a.nextN = b
        b.prev = a
    else:
        b.nextN = a
        a.prev = b
        


aNode = Node()
print (aNode.value)
