import sys
import os
class Node:
    def   __init__(self,data=None,lchild=None,rchild=None):   
                  self.data=data   
                  self.lchild=lchild   
                  self.rchild=rchild   
class BinaryTree:            
    def   __init__(self,root,func):
                  self.root=root   
                  self.func=func

def printBinaryTree(root):
    if root.lchild != None:
        printBinaryTree(root.lchild)
    print (root.data)
    if root.rchild != None:
        printBinaryTree(root.rchild)
    
root = Node(5,None,None)
parent = root
i = 0
aList=[]

while i < 10:
    tmp = Node(i,None,None)
    aList.append(tmp)
    i = i + 1
    print (tmp.data)
    
i = 1
while i < 10:
    print (aList[i].data)
    parent = aList[0]
    flag = False
    while parent != None:
        print (parent.data,i)
        if parent.data > i and parent.lchild != None:
            print ("go to left")
            parent = parent.lchild
        elif parent.data < i and parent.rchild != None:
            print ("go to right")
            parent = parent.rchild
        else:
            break
    print ("out of second while")
    if parent.data > i:
        parent.lchild = aList[i]
        print (parent.data,"is lparent of",i)
    elif parent.data < i:
        print (parent.data,"is rparent of",i) 
        parent.rchild = aList[i]
    flag = True
    i = i + 1

printBinaryTree(aList[0])

print ("game over")
        
















