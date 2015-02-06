CC=g++
CFLAGS=-std=c++11 -c -Wall
LDFLAGS=
SOURCES=dash.cpp functions.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=dash

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


