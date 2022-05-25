CC=g++
CFLAGS=-c -pedantic-errors -std=c++17
LDFLAGS=
SOURCES=boolcalc.cpp boolexpr.cpp formulaenode.cpp lib/cstring.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=boolcalc

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)