# dfs.mk

OBJS = main.o node.o
CC = g++
CFLAGS = -std=c++14 -c
LFLAGS =

# $@ - the target of this rule
# $^ - all prerequisites of this rule
dfs : $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

node.o : node.cpp node.h
	$(CC) $(CFLAGS) node.cpp

main.o : main.cpp dfs.h node.h
	$(CC) $(CFLAGS) main.cpp

clean :
	\rm *.o
