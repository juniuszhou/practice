# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: ParallelMerge
	./ParallelMerge

all:	debug test

release: ParallelMerge
ParallelMerge: ../src/ParallelMerge.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/ParallelMerge.cpp -ltbb

debug: ParallelMerge_debug
ParallelMerge_debug: ../src/ParallelMerge.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/ParallelMerge.cpp -ltbb_debug

clean:
	rm -f ParallelMerge ParallelMerge_d
