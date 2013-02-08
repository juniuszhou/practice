# Copyright 2007 Intel Corporation.  All Rights Reserved.

# Common Makefile that builds and runs examples.

# Uncomment this if you are using a 64 bit system
#x64 = 64

# Use the X11 gui
UI = x
LIBS = -lpthread -L/usr/X11R6/lib$(x64) -lX11 -lXext

# Uncomment the following two lines if you don't have lXext
#LIBS = -lpthread -L/usr/X11R6/lib$(x64) -lX11
#CXXFLAGS = -DX_NOSHMEM

# Use the console gui
#UI = con

all:	release test

release: SeismicSimulation
SeismicSimulation: ../src/gui/$(UI)video.cpp ../src/SeismicSimulation.cpp
	$(CXX) -O2 -DNDEBUG $(CXXFLAGS) -o $@ $(INCLUDE) ../src/gui/$(UI)video.cpp ../src/SeismicSimulation.cpp -ltbb $(LIBS)

debug: SeismicSimulation_d
SeismicSimulation_d: ../src/gui/$(UI)video.cpp ../src/SeismicSimulation.cpp
	$(CXX) -g -O0 -DTBB_DO_ASSERT $(CXXFLAGS) -o $@ $(INCLUDE) ../src/gui/$(UI)video.cpp ../src/SeismicSimulation.cpp -ltbb_debug $(LIBS)

clean:
	rm -f SeismicSimulation SeismicSimulation_d

test:
	./SeismicSimulation
