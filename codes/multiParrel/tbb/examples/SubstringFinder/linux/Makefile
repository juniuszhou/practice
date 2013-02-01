# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: SubstringFinder
	./SubstringFinder

all:	debug test

release: SubstringFinder
SubstringFinder: ../src/SubstringFinder.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/SubstringFinder.cpp -ltbb

debug: SubstringFinder_debug
SubstringFinder_debug: ../src/SubstringFinder.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/SubstringFinder.cpp -ltbb_debug

clean:
	rm -f SubstringFinder SubstringFinder_d
