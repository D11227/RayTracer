CC = g++

CFLAGSO = -std=c++17 -Wall
OUTPUT = image

build:
	${CC} *.cpp ${CFLAGSO} -o main
	./main > ${OUTPUT}.ppm
