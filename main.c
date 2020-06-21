#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "grid.h"
#include "vect.h"

static bool running = true;

void handleInput(char ch);

void showLastPressed(char ch);

int main()
{ 
	// init 
	initscr();
	raw();
	
	// Colors
	// allows for transparancy when color values in init_pair(); are set to -1 or, no pair specified
	// e.g init_pair(1, COLOR_WHITE, -1) would be transparent background but white text
	use_default_colors();
	start_color();
	// cell
	init_pair(1, COLOR_BLUE, COLOR_WHITE);
	// text
	init_pair(2, COLOR_YELLOW, -1);

	// doesn't wait for user to input.
	// timeout(100) waits for 100ms for input.
	timeout(0); 	
	curs_set(FALSE);

	int width = 0;
	int height = 0;

	// stdscr is screen created by initscr()
	getmaxyx(stdscr, height, width);

	// framerate of the game 
	const int FRAME_RATE = 144;
	const float FRAME_TIME = 1.f/(float)FRAME_RATE;

	Grid grid;
	initGrid(&grid, width, height);
	randomizeGrid(&grid);

	float t = 0;
	while (running) {
		clock_t start_t = clock();
		char ch = getch();

		handleInput(ch);

		// draw grid
		drawGrid(&grid);
		// draw overlays
		attron(COLOR_PAIR(2));
		showLastPressed(ch);
		attroff(COLOR_PAIR(2));

		refresh();
		updateGrid(&grid);

		usleep(pow(10,6)*(FRAME_TIME-t));
		float t = (float) (clock()-start_t) / (float) CLOCKS_PER_SEC;

	}

	endwin();
	return 0;
}

void showLastPressed(char ch)
{
	static char lastc = ' ';
	if (ch != -1) lastc = ch;
	mvprintw(0, 0, "LastPressed: %c", lastc);
}
void handleInput(char ch)
{
	if (ch == 'q') running = false;  
}
