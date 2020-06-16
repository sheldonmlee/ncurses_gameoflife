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

	//hz
	const int FRAME_RATE = 10;

	const int DELAY = (float)pow(10,6)/(float)FRAME_RATE;

	Grid grid;
	initGrid(&grid, width, height);
	randomizeGrid(&grid);

	while (running) {
		drawGrid(&grid);

		refresh();

		updateGrid(&grid);

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
