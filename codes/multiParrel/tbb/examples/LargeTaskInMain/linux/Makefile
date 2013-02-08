# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: LargeTaskInMain
	./LargeTaskInMain

all:	debug test

release: LargeTaskInMain
LargeTaskInMain: ../src/LargeTaskInMain.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/LargeTaskInMain.cpp -ltbb

debug: LargeTaskInMain_debug
LargeTaskInMain_debug: ../src/LargeTaskInMain.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/LargeTaskInMain.cpp -ltbb_debug

clean:
	rm -f LargeTaskInMain LargeTaskInMain_d
