import os

import time
 
def timeit(func):
    def wrapper():
        start = time.clock()        
        end =time.clock()
        print 'used:', end - start
        func()
    return wrapper
 
@timeit
def foo():
    print 'in foo() *******'
 
foo()
foo()
foo()
foo()


