CC=g++
CFLAGS=-Wall -Iinclude -c
LFLAGS=-Wall
LLVMFLAGS=`llvm-config --cxxflags --ldflags --libs core`

OBJECTS=\
build/scanner.o \
build/parser.o \
build/scanner_driver.o \
build/foamyc.o \
build/codegen.o

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
	$(CC) $(LLVMFLAGS) $(CFLAGS) src/codegen.cpp -o build/codegen.o

build/foamyc.o: src/foamyc.cpp
	$(CC) $(LLVMFLAGS) $(CFLAGS) src/foamyc.cpp -o build/foamyc.o
	
build/printer.o: src/printer_driver.cpp
	$(CC) $(LLVMFLAGS) $(CFLAGS) src/printer_driver.cpp -o build/printer.o

bin/scanner: build/scanner_driver.o build/scanner.o build/parser.o
	$(CC) $(LFLAGS) -o bin/scanner build/scanner_driver.o build/scanner.o build/parser.o

bin/foamyc: build/foamyc.o build/scanner.o build/parser.o build/codegen.o
	$(CC) $(LFLAGS) -o bin/scanner build/scanner_driver.o build/scanner.o build/parser.o

bin/winning: build/scanner.o build/parser.o build/codegen.o build/printer.o
	$(CC) $(LLVMFLAGS) $(LFLAGS) -o bin/printer \
	build/scanner.o build/parser.o build/codegen.o build/printer.o

bin/working: build/scanner.o build/parser.o build/printer.o
	$(CC) $(LLVMFLAGS) $(LFLAGS) -o bin/printer \
	build/scanner.o build/parser.o build/printer.o
