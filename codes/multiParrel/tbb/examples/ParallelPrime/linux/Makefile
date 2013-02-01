# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: ParallelPrime
	./ParallelPrime

all:	debug test

release: ParallelPrime
ParallelPrime: ../src/ParallelPrime.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/ParallelPrime.cpp -ltbb

debug: ParallelPrime_debug
ParallelPrime_debug: ../src/ParallelPrime.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/ParallelPrime.cpp -ltbb_debug

clean:
	rm -f ParallelPrime ParallelPrime_d
