CC=g++
CFLAGS=-std=c++11 -c -Wall
LDFLAGS=
SOURCES=mmu.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mmu

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


