#  Group 4
#   Melvin Abraham    170013110
#   Kamila Gorska     170013107
#   Charlie Hewitt    170015454
#   Caoilainn McCrory 170001498
#   Frantisek Pavlica 170020274


CC = g++
CFLAGS = -Wextra -Wall -pedantic

all: baby assembler

baby: baby.o line.o
	$(CC) -std=c++14 $(CFLAGS) -o baby baby.o line.o
	
baby.o: baby.cpp baby.h line.h
	$(CC) $(CFLAGS) -c baby.cpp

line.o: line.cpp line.h
	$(CC) $(CFLAGS) -c line.cpp
	
assembler: assembler.cpp
	$(CC) $(CFLAGS) -o assembler assembler.cpp
