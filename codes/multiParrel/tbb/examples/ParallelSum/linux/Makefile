# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: ParallelSum
	./ParallelSum

all:	debug test

release: ParallelSum
ParallelSum: ../src/ParallelSum.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/ParallelSum.cpp -ltbb

debug: ParallelSum_debug
ParallelSum_debug: ../src/ParallelSum.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/ParallelSum.cpp -ltbb_debug

clean:
	rm -f ParallelSum ParallelSum_d
