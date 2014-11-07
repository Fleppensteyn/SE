CXX = $(shell wx-config --cxx)

PROGRAM = main
CCFLAGS =$(shell curl-config --cflags) $(shell curl-config --libs) $(shell wx-config --cxxflags) $(shell wx-config --libs)
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp)) $(patsubst %.cpp,%.o,$(wildcard sha1/*.cpp))

# implementation

.SUFFIXES:      .o .cpp

.cpp.o :
	$(CXX) -c  -o $@ $<  $(CCFLAGS)

all:    $(PROGRAM)

$(PROGRAM):     $(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) $(CCFLAGS)

clean:
	rm -f *.o sha1/*.o $(PROGRAM) $(PROGRAM).exe