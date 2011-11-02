CC=g++
CFLAGS=-Wall -Iinclude -c
LFLAGS=-Wall

OBJECTS=\
build/scanner.o \
build/scanner_driver.o

default: bin/scanner

.PHONY : clean
clean:
	rm -f build/*.o
	rm -f bin/scanner

.PHONY : compile
compile: $(OBJECTS)

build/scanner.o: src/scanner.cpp include/scanner.hpp
	$(CC) $(CFLAGS) src/scanner.cpp -o build/scanner.o

build/scanner_driver.o: src/scanner_driver.cpp
	$(CC) $(CFLAGS) src/scanner_driver.cpp -o build/scanner_driver.o

bin/scanner: build/scanner_driver.o build/scanner.o
	$(CC) $(LFLAGS) -o bin/scanner build/scanner_driver.o build/scanner.o
