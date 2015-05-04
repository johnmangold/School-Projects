CC=g++
CFLAGS=-std=c++11 -c -w
LDFLAGS=
SOURCES=Prog3.cpp process.cpp mmu.cpp pra.cpp mailbox.cpp mailbox_functions.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=prog3

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

