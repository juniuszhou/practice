# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: FeedTwoMouths
	./FeedTwoMouths

all:	debug test

release: FeedTwoMouths
FeedTwoMouths: ../src/FeedTwoMouths.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/FeedTwoMouths.cpp -ltbb

debug: FeedTwoMouths_debug
FeedTwoMouths_debug: ../src/FeedTwoMouths.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/FeedTwoMouths.cpp -ltbb_debug

clean:
	rm -f FeedTwoMouths FeedTwoMouths_d
