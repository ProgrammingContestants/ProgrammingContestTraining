CC=g++
CFLAGS=-W -ansi -pedantic -Wunreachable-code -O2 -g
LDFLAGS=
SOURCES=main.cpp $(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main.out

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm src/*.o $(EXECUTABLE)
