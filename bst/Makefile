# main.mk

OBJS = main.o

CC = g++
CFLGS = -std=c++14 -c
LFLGS =

main : $(OBJS)
	$(CC) $(LFLGS) $^ -o $@

main.o : main.cpp bst.h
	$(CC) $(CFLGS) main.cpp
