# findpermutation.mk

OBJS = findpermutation.o twotuple.o
CC = g++
CFLAGS = -std=c++14 -c
LFLAGS = -s

# $@ - the target of this rule
# $^ - all prerequisites of this rule
findpermutation : $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

twotuple.o : twotuple.cpp twotuple.h
	$(CC) $(CFLAGS) twotuple.cpp

findpermutation.o : findpermutation.cpp twotuple.h
	$(CC) $(CFLAGS) findpermutation.cpp

clean :
	\rm *.o
