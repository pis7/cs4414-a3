.SILENT:
.PHONY: clean run debug zip

DIR = SpeciesData
CFLAGS = -Wall

build/hw3: src/Animal.cpp src/Gene.cpp src/hw3.cpp 
	mkdir -p build
	g++ -std=c++2a $(CFLAGS) $^ -o $@

run: build/hw3
	./$< ${DIR}

debug: CFLAGS += -g
debug: clean build/hw3
	gdb ./build/hw3

zip:
	zip -rj hw3.zip src/

clean:
	rm -rf build/
	rm -rf *.zip