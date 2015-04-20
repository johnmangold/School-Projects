CC=g++
CFLAGS=-std=c++11 -c -Wall
LDFLAGS=
SOURCES=b17.cpp b17_functions.cpp base_conversion.cpp decode.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=b17

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


