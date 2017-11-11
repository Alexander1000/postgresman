BIN_DIR=$(shell pwd)/bin

build:
	g++ -Wall -pedantic main.cpp -dynamiclib -o ${BIN_DIR}/main.o \
    && g++ ${BIN_DIR}/main.o -o ${BIN_DIR}/postgresman
