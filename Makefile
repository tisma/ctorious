OBJS = ptrace.o #delete_duplicates.o
CFLAGS = -Wall -g
#CPPFLAGS = -std=c++11
CC = gcc
CPP = g++
#LIBS = 

ptrace: ptrace.o
	${CC} ${CFLAGS} -o $@ ${OBJS} ${LIBS}

#delete_duplicates: delete_duplicates.o
#	${CPP} ${CPPFLAGS} -o $@ ${OBJS} ${LIBS}
clean:
	rm -f *.o

