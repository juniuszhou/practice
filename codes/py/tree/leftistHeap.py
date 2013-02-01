import os

class Node:
   length = 0
   data = 0
   def   __init__(self,data=0,length=0):
                  self.data=data
                  self.length=length                  
                  self.lchild=None                  
                  self.rchild=None

def Merge(aTree,bTree):
    if aTree == None:
        return bTree
    if bTree == None:
        return aTree
    if aTree.data > bTree.data:
        tmp = aTree
        aTree = bTree
        bTree = tmp
    aTree.rchild = Merge(aTree.rchild,bTree)
    if aTree.rchild != Node and aTree.lchild != Node:
        if aTree.rchild.length > aTree.lchild.length:
            tmp = aTree.lchild
            aTree.lchild = aTree.rchild
            aTree.rchild = tmp
    if aTree.rchild == None:
        aTree.length = 0
    else:
        aTree.length = aTree.rchild.length + 1
    return aTree

def headFirst(aTree):
    if aTree == None:
        return
    print (aTree.data)
    if aTree.lchild != Node:
        headFirst(aTree.lchild)
    if aTree.rchild != Node:
        headFirst(aTree.rchild)    
# http://blog.csdn.net/king821221/article/details/2068668

def create(aTree,value):
    aTree = Node()
    aTree.data = value
    aTree.length = 0

root = Node()
root.data = 0

i = 1
while i < 2:
    tmp = Node
    tmp.data = i
    Merge(root,tmp)
    i = i + 1
headFirst(root)
    
    
