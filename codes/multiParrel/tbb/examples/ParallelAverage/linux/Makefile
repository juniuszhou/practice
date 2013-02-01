# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: ParallelAverage
	./ParallelAverage

all:	debug test

release: ParallelAverage
ParallelAverage: ../src/ParallelAverage.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/ParallelAverage.cpp -ltbb

debug: ParallelAverage_debug
ParallelAverage_debug: ../src/ParallelAverage.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/ParallelAverage.cpp -ltbb_debug

clean:
	rm -f ParallelAverage ParallelAverage_d
