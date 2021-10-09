SRCS:=${wildcard src/*.cpp}

OPTS:= -Iinclude -pthread -lpthread -L../lib -li2c -std=c++11

.PHONY: calib read

all: calib read

read: 
	mkdir -p bin
	g++ ./test/read.cpp ${SRCS} -o bin/read ${OPTS}

calib: 
	mkdir -p bin
	g++ ./test/calib.cpp ${SRCS} -o bin/calib ${OPTS}

server:
	mkdir -p bin
	g++ ./test/server.cpp ${SRCS} -o bin/server ${OPTS}
client:
	mkdir -p bin
	g++ ./test/client.cpp ${SRCS} -o bin/client ${OPTS}