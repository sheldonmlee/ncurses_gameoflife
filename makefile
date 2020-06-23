LDFLAGS=-lncurses

main: *.c
	gcc *.c -o main ${LDFLAGS}
