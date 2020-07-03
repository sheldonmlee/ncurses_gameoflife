LDFLAGS=-lncurses
CC=gcc


main: *.c
	$(CC) *.c -o main ${LDFLAGS}

