LDFLAGS=-lncurses

main: main.c grid.c vect.c
	gcc main.c grid.c vect.c -o main ${LDFLAGS}
