CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp TSP.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tsp

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
