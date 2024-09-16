

all: test

test: build/q4x_test
	./build/q4x_test

build/q4x_test: qspi4xy2-100_tb.c build
	gcc -o build/q4x_test qspi4xy2-100_tb.c -I./

build:
	mkdir -p build

clean:
	rm -rf build

