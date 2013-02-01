# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

test: ODE_simulate
	./ODE_simulate

all:	debug test

release: ODE_simulate
ODE_simulate: ../src/ODE_simulate.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/ODE_simulate.cpp -ltbb

debug: ODE_simulate_debug
ODE_simulate_debug: ../src/ODE_simulate.cpp
	$(CXX) -O0 -g -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/ODE_simulate.cpp -ltbb_debug

clean:
	rm -f ODE_simulate ODE_simulate_d
