.SILENT:
.PHONY: clean run

DIR = SpeciesData

build/hw3: src/Animal.cpp src/Gene.cpp src/hw3.cpp 
	mkdir -p build
	g++ -std=c++2a -Wall $^ -o $@

run: build/hw3
	./$< ${DIR}

clean:
	rm -rf build/