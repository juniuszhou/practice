# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: CountStrings
	./CountStrings

all:	debug test

release: CountStrings
CountStrings: ../src/CountStrings.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/CountStrings.cpp -ltbb

debug: CountStrings_debug
CountStrings_debug: ../src/CountStrings.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/CountStrings.cpp -ltbb_debug

clean:
	rm -f CountStrings CountStrings_d
