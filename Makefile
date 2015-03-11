OBJS = ptrace.o
CFLAGS = -Wall -g
CC = gcc
LIBS = 

ptrace: ptrace.o
	${CC} ${CFLAGS} -o $@ ${OBJS} ${LIBS}

clean:
	rm -f *.o

