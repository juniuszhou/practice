# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: Strassen
	./Strassen

all:	debug test

release: Strassen
Strassen: ../src/Strassen.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/Strassen.cpp -ltbb

debug: Strassen_debug
Strassen_debug: ../src/Strassen.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/Strassen.cpp -ltbb_debug

clean:
	rm -f Strassen Strassen_d
