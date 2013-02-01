# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: PacketProcessing
	./PacketProcessing ../data/input.txt

all:	debug test

release: PacketProcessing
PacketProcessing: ../src/PacketProcessing.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/PacketProcessing.cpp -ltbb

debug: PacketProcessing_debug
PacketProcessing_debug: ../src/PacketProcessing.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/PacketProcessing.cpp -ltbb_debug

clean:
	rm -f PacketProcessing PacketProcessing_d
