import os
import sys
import shutil
print ("the path will be",sys.argv[1])
a=os.listdir(sys.argv[1])

for name in a:    
    newName = 'm' + name.capitalize()
    print (name)
    print (newName)
    os.rename(name,newName)
    
exit
