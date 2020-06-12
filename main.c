#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>
#include "grid.h"
#include "vect.h"

static volatile int running = 1;

static void contain(int* pos, int* velocity, int min, int max);
// if ^C is pressed, set running flag to false 
static void signalHandler(int sig);

int main()
{ 
	signal(SIGINT, signalHandler);
	int count = 0; 
	//init 
	initscr();
	//noecho();
	
	curs_set(FALSE);
	int width = 0;
	int height = 0;

	// stdscr created by initscr()
	getmaxyx(stdscr, height, width);

	Vect2i pos = {0, 0};
	Vect2i vel = {1, 1};

	const int DELAY = 33*pow(10,3);

	Grid grid;
	initGrid(&grid, width, height);
	putPixel(&grid, pos.x, pos.y);

	while (running) {
		clearGrid(&grid);
		putPixel(&grid, pos.x, pos.y);
		drawGrid(&grid);

		refresh();

		moveVect2i(&pos, vel.x, vel.y);
		contain(&pos.x, &vel.x, 0, width-1);
		contain(&pos.y, &vel.y, 0, height-1);

		usleep(DELAY);
	}

	endwin();
	return 0;
}

static void contain(int* pos, int* velocity, int min, int max)
{
	bool above_max = max < *pos;
	bool below_min = *pos < min;
	bool not_in_range =  below_min || above_max;
	if (not_in_range) {
		if (below_min) *pos = min;
		else if (above_max) *pos = max;
		*velocity *= -1;
	}
}

static void signalHandler(int sig)
{
	printf("interrupt\n");
	running = 0;
}
