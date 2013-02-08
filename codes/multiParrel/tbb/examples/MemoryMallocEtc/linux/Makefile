# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: MemoryMallocEtc
	./MemoryMallocEtc

all:	debug test

release: MemoryMallocEtc
MemoryMallocEtc: ../src/MemoryMallocEtc.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/MemoryMallocEtc.cpp -ltbbmalloc

debug: MemoryMallocEtc_debug
MemoryMallocEtc_debug: ../src/MemoryMallocEtc.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/MemoryMallocEtc.cpp -ltbbmalloc_debug

clean:
	rm -f MemoryMallocEtc MemoryMallocEtc_d
