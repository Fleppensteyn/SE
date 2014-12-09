CXX = g++
CC  = gcc

PROGRAM = CurriculumBuilder
CFLAGS = -Wall -Wextra
WXFLAGS = $(shell wx-config --cxxflags)
CURLFLAGS = $(shell curl-config --cflags)
LDFLAGS = $(shell curl-config --libs) $(shell wx-config --libs) -lpthread -ldl
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp)) $(patsubst %.cpp,%.o,$(wildcard */*.cpp))

.SUFFIXES: .o .cpp

.cpp.o :
	$(CXX) -c -o $@ $< $(CFLAGS) $(WXFLAGS)

all: $(PROGRAM)

$(PROGRAM): sqlite/sqlite3.o $(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) sqlite/sqlite3.o $(CFLAGS) $(LDFLAGS)

ServerCommunication.o: ServerCommunication.cpp
	$(CXX) -c -o ServerCommunication.o ServerCommunication.cpp $(CURLFLAGS)

main.o: main.cpp
	$(CXX) -c -o main.o main.cpp $(CURLFLAGS) $(WXFLAGS)

sha1/sha1.o: sha1/sha1.cpp
	$(CXX) -c sha1/sha1.cpp -o sha1/sha1.o $(CFLAGS)

sqlite/sqlite3.o: sqlite/sqlite3.c
	$(CC) -c -o sqlite/sqlite3.o sqlite/sqlite3.c

sqlite/sqlite3.c:
	unzip sqlite.zip

clean:
	rm -f *.o */*.o $(PROGRAM) $(PROGRAM).exe