C = gcc
CFLAGS = -Wall -g -std=c11
LDLIBS = -lm
ALL = mpsh

all :	$(ALL)
mpsh :	mpsh.c
cleanall:
	rm -rf *~ *.o $(ALL)