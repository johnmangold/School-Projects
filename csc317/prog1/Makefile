CC=g++
CFLAGS=-std=c++11 -c -Wall
LDFLAGS=
SOURCES=Hamming.cpp functions.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Hamming

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


