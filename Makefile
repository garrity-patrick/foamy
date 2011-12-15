CC=g++
CFLAGS=-Wall -Iinclude -c
LFLAGS=-Wall
LLVMFLAGS=`llvm-config --cxxflags --ldflags --libs core`

OBJECTS=\
build/scanner.o \
build/parser.o \
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
	
build/parser.o:	src/parser.cpp include/parser.hpp
	$(CC) $(CFLAGS) src/parser.cpp -o build/parser.o

build/scanner_driver.o: src/scanner_driver.cpp
	$(CC) $(CFLAGS) src/scanner_driver.cpp -o build/scanner_driver.o 

build/codegen.o: src/codegen.cpp include/codegen.hpp include/vartable.hpp
	$(CC) $(LLVMFLAGS) $(CFLAGS) src/codegen.cpp -o build/codegen.cpp

bin/scanner: build/scanner_driver.o build/scanner.o build/parser.o build/codegen.o
	$(CC) $(LLVMFLAGS) $(LFLAGS) -o bin/scanner build/scanner_driver.o build/scanner.o build/parser.o build/codegen.o



bin/printer: .PHONY
	$(CC) -Iinclude -o bin/printer src/printer_driver.cpp
	clear
	bin/printer
