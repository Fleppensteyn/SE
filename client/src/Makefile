CXX = $(shell wx-config --cxx) -Wall -Wextra

PROGRAM = CurriculumBuilder
CCFLAGS =$(shell curl-config --cflags) $(shell curl-config --libs) $(shell wx-config --cxxflags) $(shell wx-config --libs) -lpthread -ldl
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp)) $(patsubst %.cpp,%.o,$(wildcard sha1/*.cpp)) $(patsubst %.cpp,%.o,$(wildcard newmouseman/*.cpp))

# implementation

.SUFFIXES:      .o .cpp


.cpp.o :
	$(CXX) -c  -o $@ $<  $(CCFLAGS)

all:  $(PROGRAM)

$(PROGRAM): sqlite/sqlite3.o $(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) sqlite/sqlite3.o $(CCFLAGS)

sqlite/sqlite3.o: sqlite/sqlite3.c
	gcc -c -o sqlite/sqlite3.o sqlite/sqlite3.c

sqlite/sqlite3.c:
	unzip sqlite.zip


clean:
	rm -f *.o sha1/*.o sqlite/*.o newmouseman/*.o $(PROGRAM) $(PROGRAM).exe