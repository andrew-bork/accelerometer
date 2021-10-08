SRCS:=${wildcard src/*.cpp}

OPTS:= -Iinclude -pthread -lpthread -L../lib -li2c -std=c++11

.PHONY: calib

all: calib

calib: 
	mkdir -p bin
	g++ ./test/calib.cpp ${SRCS} -o bin/calib ${OPTS}