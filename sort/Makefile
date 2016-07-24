# quicksort.mk

OBJS = main.o
CC = g++
CFLAGS = -std=c++14 -c
LFLAGS = -s

# $@ - the target of this rule
# $^ - all prerequisites of this rule
quicksort : $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

main.o : main.cpp quicksort.h
	$(CC) $(CFLAGS) main.cpp

clean :
	\rm *.o
