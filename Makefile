.SILENT:
.PHONY: clean run

DIR = SpeciesData
CFLAGS = -Wall

build/hw3: src/Animal.cpp src/Gene.cpp src/hw3.cpp 
	mkdir -p build
	g++ -std=c++2a $(CFLAGS) $^ -o $@

run: build/hw3
	./$< ${DIR}

debug: CFLAGS += -g
debug: build/hw3
	gdb ./build/hw3

clean:
	rm -rf build/