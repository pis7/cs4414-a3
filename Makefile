.SILENT:
.PHONY: clean run run-hw3 run-ptree debug debug-hw3 debug-ptree zip

DIR = SpeciesData
ROOT = 0
LVL = 0
CFLAGS = -Wall

# Compile individual source files
build/Animal.o: src/Animal.cpp
	mkdir -p build
	g++ -std=c++2a $(CFLAGS) -c $< -o $@

build/Gene.o: src/Gene.cpp
	mkdir -p build
	g++ -std=c++2a $(CFLAGS) -c $< -o $@

build/PhylogenyTree.o: src/PhylogenyTree.cpp
	mkdir -p build
	g++ -std=c++2a $(CFLAGS) -c $< -o $@

# Compile and link for hw3
build/hw3: build/Animal.o build/Gene.o src/hw3.cpp
	mkdir -p build
	g++ -std=c++2a $(CFLAGS) $^ -o $@

# Compile and link for ptree
build/ptree: build/Animal.o build/Gene.o build/PhylogenyTree.o src/ptree.cpp
	mkdir -p build
	g++ -std=c++2a $(CFLAGS) $^ -o $@

run-hw3: build/hw3
	./build/hw3 ${DIR}

run-ptree: build/ptree
	./build/ptree ${ROOT} ${LVL}

debug-hw3: CFLAGS += -g
debug-hw3: clean build/hw3
	gdb ./build/hw3

debug-ptree: CFLAGS += -g
debug-ptree: clean build/ptree
	gdb ./build/ptree

zip:
	zip -rj hw3.zip src/

clean:
	rm -rf build/
	rm -rf *.zip
