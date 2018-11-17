CC = g++
CFLAGS = -Wextra -Wall -pedantic

all: baby.o line.o
	$(CC) -std=c++14 $(CFLAGS) -o baby baby.o line.o
	
baby.o: baby.cpp baby.h line.h
	$(CC) $(CFLAGS) -c baby.cpp

line.o: line.cpp line.h
	$(CC) $(CFLAGS) -c line.cpp