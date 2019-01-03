C = gcc
CFLAGS = -Wall -g -std=c11
LDLIBS = -lm
OBJS = var.o varutils.o mpsh.o commands.o
ALL = mpsh

all :	$(ALL)

var.o : var.c
varutils.o : varutils.c
mpsh.o : mpsh.c
commands.o : commands.c
mpsh : $(OBJS)
testvar : testvar.c var.o
testvarutils : testvarutils.c varutils.o
cleanall:
	rm -rf *~ *.o $(ALL)