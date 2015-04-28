CC=g++
CFLAGS=-std=c++11 -c -Wall
LDFLAGS=
SOURCES=mailbox.cpp mailbox_functions.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mailbox

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


