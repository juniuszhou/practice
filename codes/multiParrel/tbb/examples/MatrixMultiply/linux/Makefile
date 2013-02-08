# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: MatrixMultiply
	./MatrixMultiply

all:	debug test

release: MatrixMultiply
MatrixMultiply: ../src/MatrixMultiply.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/MatrixMultiply.cpp -ltbb

debug: MatrixMultiply_debug
MatrixMultiply_debug: ../src/MatrixMultiply.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/MatrixMultiply.cpp -ltbb_debug

clean:
	rm -f MatrixMultiply MatrixMultiply_d
