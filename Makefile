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

test: all
	@failed=0; \
	for i in 01 02 03 04 05 06 07 08 09 10; do \
		printf "Test $$i: "; \
		if ./$(EXECUTABLE) -isfull tests/funs$$i.in output.txt && cmp -s output.txt tests/funs$$i.out; then \
			echo "PASS"; \
		else \
			echo "FAIL"; \
			failed=$$((failed + 1)); \
		fi; \
	done; \
	rm -f output.txt; \
	if [ "$$failed" -gt 0 ]; then echo "$$failed test(s) failed"; exit 1; fi; \
	echo "All tests passed"

clean:
	rm -rf *.o $(EXECUTABLE)