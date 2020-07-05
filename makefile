LDFLAGS=-lncurses
FLAGS=-Wall
CC=gcc


main: *.c
	$(CC) *.c ${FLAGS} -o main ${LDFLAGS}

clean:
	rm main
	$(CC) *.c ${FLAGS} -o main ${LDFLAGS}

