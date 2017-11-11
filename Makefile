BIN_DIR=$(shell pwd)/bin

build:
	g++ main.cpp -dynamiclib -o ${BIN_DIR}/main.o
	g++ ${BIN_DIR}/main.o -o ${BIN_DIR}/postgresman
