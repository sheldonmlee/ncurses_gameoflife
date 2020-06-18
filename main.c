#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "grid.h"
#include "vect.h"


static void contain(int* pos, int* velocity, int min, int max);

int main()
{ 
	// init 
	bool running = true;
	initscr();
	raw();
	// doesn't wait for user to input.
	// timeout(100) waits for 100ms for input.
	timeout(0); 	
	curs_set(FALSE);

	int width = 0;
	int height = 0;

	// stdscr is screen created by initscr()
	getmaxyx(stdscr, height, width);

	// hz
	const int FRAME_RATE = 100;

	const int DELAY = (float)pow(10,6)/(float)FRAME_RATE;

	Grid grid;
	initGrid(&grid, width, height);
	randomizeGrid(&grid);

	clock_t t = 0;
	while (running) {
		clock_t start_t = clock();
		char ch = getch();
		if (ch == 'q') running = false;  

		drawGrid(&grid);

		refresh();

		updateGrid(&grid);
		t += clock()-start_t;

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
