#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "grid.h"
#include "vect.h"

int main()
{ 
	// init 
	bool running = true;
	initscr();
	raw();
	// allows for transparancy when color values in init_pair(); are set to -1 or, no pair specified
	// e.g init_pair(1, COLOR_WHITE, -1) would be transparent background but white text
	use_default_colors();
	start_color();
	// doesn't wait for user to input.
	// timeout(100) waits for 100ms for input.
	timeout(0); 	
	curs_set(FALSE);

	int width = 0;
	int height = 0;

	// stdscr is screen created by initscr()
	getmaxyx(stdscr, height, width);

	// framerate of the game 
	const int FRAME_RATE = 30;
	const float FRAME_TIME = 1.f/(double)FRAME_RATE;

	const int DELAY = (float)pow(10,6)/(float)FRAME_RATE;

	Grid grid;
	initGrid(&grid, width, height);
	randomizeGrid(&grid);

	clock_t t = 0;
	while (running) {
		clock_t start_t = clock();
		char ch = getch();
		if (ch == 'q') running = false;  

		float actual_frame_time = (float) t / (float) CLOCKS_PER_SEC;

		if (actual_frame_time >= FRAME_TIME) {
			drawGrid(&grid);
			refresh();
			updateGrid(&grid);
			t = 0;
		}

		t += clock()-start_t;

	}

	endwin();
	return 0;
}

