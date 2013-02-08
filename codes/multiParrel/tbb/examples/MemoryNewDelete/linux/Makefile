# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: MemoryNewDelete
	./MemoryNewDelete

all:	debug test

release: MemoryNewDelete
MemoryNewDelete: ../src/MemoryNewDelete.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/MemoryNewDelete.cpp -ltbb -ltbbmalloc

debug: MemoryNewDelete_debug
MemoryNewDelete_debug: ../src/MemoryNewDelete.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/MemoryNewDelete.cpp -ltbb_debug -ltbbmalloc_debug

clean:
	rm -f MemoryNewDelete MemoryNewDelete_d
