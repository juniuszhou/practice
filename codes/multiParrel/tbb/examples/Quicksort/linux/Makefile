# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: Quicksort
	./Quicksort

all:	debug test

release: Quicksort
Quicksort: ../src/Quicksort.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/Quicksort.cpp -ltbb

debug: Quicksort_debug
Quicksort_debug: ../src/Quicksort.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/Quicksort.cpp -ltbb_debug

clean:
	rm -f Quicksort Quicksort_d
