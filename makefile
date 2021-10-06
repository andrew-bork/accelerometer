SRCS:=${wildcard src/*.cpp}

OPTS:= -Iinclude -pthread -lpthread -L../lib -li2c -std=c++11

.PHONY: accel

all: accel

accel: 
	mkdir -p bin
	g++ ${SRCS} -o bin/drone ${OPTS}