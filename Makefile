BIN_DIR=$(shell pwd)/bin

build:
	rm -f ./bin/*.o \
    && g++ -Wall -pedantic main.cpp -dynamiclib -o ${BIN_DIR}/main.o \
    && g++ ${BIN_DIR}/main.o -o ${BIN_DIR}/postgresman

test: build
	./bin/postgresman -i $(shell pwd)/sample/sample_01.sql \
    && ./bin/postgresman -i ./sample/sample_02.sql
