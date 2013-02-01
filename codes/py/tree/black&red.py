import sys

# 0 is for black 1 is for red
class Node:
   def   __init__(self,data=0,color=0,lchild=None,rchild=None):   
                  self.data=data
                  self.color=color
                  self.lchild=lchild   
                  self.rchild=rchild
                  
def rotateLeft(head):
    pass
    
def rotateLeft(head):
    pass

def rotateRight(head):
    pass

def printTree(head):
   if head == None:
      return
   if head.lchild != None:
      printTree(head.lchild)
   print (head.data," color is ",head.color)
   if head.rchild != None:
      printTree(head.rchild)
   
def addNode(head,node):
    if head == None or node == None:
        return node
    tmpPoint = head
    tmpParent = head
    while tmpPoint != None:
        tmpParent = tmpPoint
        if tmpPoint.data > node.data:            
            tmpPoint = tmpPoint.lchild
        else:
            tmpPoint = tmpPoint.rchild
    if tmpParent.data > node.data:
        tmpParent.lchild = node
    else:
        tmpParent.rchild = node
        
    if tmpParent.color == 0:
        return
#    checkColor(head,tmpParen)

file = open('input.txt','r+')
aTree = Node(23,0)
for eachline in file:
   print ("hello")
   tmpNode = Node(int(eachline),1)
   addNode(aTree,tmpNode)
file.close()
printTree(aTree)





#def removeNode(head,node):

#output tree bfs
#def outputTree(head):

print ("compile is ok")
    
    
