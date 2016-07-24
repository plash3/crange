# editdistance.mk

OBJS = editdistance.o twotuple.o
CC = g++
CFLAGS = -std=c++14 -c
LFLAGS = -s

# $@ - the target of this rule
# $^ - all prerequisites of this rule
editdistance : $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

twotuple.o : twotuple.cpp twotuple.h
	$(CC) $(CFLAGS) twotuple.cpp

editdistance.o : editdistance.cpp twotuple.h
	$(CC) $(CFLAGS) editdistance.cpp

clean :
	\rm *.o
