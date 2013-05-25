import sys
import os
import string 
##capitalize just works for first character is letter
strGlobe = "i am a gentle man"
print (strGlobe.capitalize())

strGlobe = " i am a gentle man"
print (strGlobe.capitalize())

##center output is #######gentle#######
strGlobe = "gentle"
print (strGlobe.center(20,"#"))

##count output is 2
strGlobe = " i am a gentle man gentle"
subStr = "gentle"
print (strGlobe.count(subStr))

##encode

##endswith, output is true
strGlobe = "man gentle"
subStr = "gentle"
print (strGlobe.endswith(subStr))

##expandtabs to replace tab with spaces, default is 8
strGlobe = "\tgentle\t"
print (strGlobe.expandtabs(15))

##find
strGlobe = "man gentle"
subStr = "gentle"
print (strGlobe.find(subStr))

##index, similar to find, but raise error if not found
strGlobe = "man gentle"
subStr = "gentle"
print (strGlobe.index(subStr))

##isalnum isalpha isdigit islower  isspace istitle isupper 

##join
print ("".join([str(x) for x in range(7)]))

conf = {'host':'127.0.0.1','db':'spam','user':'sa','passwd':'eggs'}
print (';'.join("%s=%s"%(k, v) for k, v in conf.iteritems()))

##ljust lower lstrip replace rfind rindex rjust rstrip

##split
strGlobe = "i am a gentle man gentle"
aList = strGlobe.split(" ")
print (aList)

##splitlines equal split("\n")
##startswith strip swapcase  title upper

##translate
strGlobe = "i am a from man from"
s = b'abcdefg-1234567'
#table = b''.maketrans(b'abc', b'ABC')
print (strGlobe.translate(string.maketrans("from", "toto")))

##reference some const string defined in string module
print (string.ascii_letters)
print ("game over")

##format a string
x = 123
print ('%d' % x)


print ("game over")

