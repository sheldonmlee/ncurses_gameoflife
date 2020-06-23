#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "grid.h"
#include "vect.h"

static bool running = true;
static bool do_step = true;
static Vect2i cursor = {0, 0};

void handleInput(char ch);

void showLastPressed(char ch);

void showCurPos();

int main()
{ 
	// init 
	initscr();
	raw();
	noecho();
	
	// Colors
	// allows for transparancy when color values in init_pair(); are set to -1 or, no pair specified
	// e.g init_pair(1, COLOR_WHITE, -1) would be transparent background but white text
	use_default_colors();
	start_color();
	// cell
	init_pair(1, COLOR_BLUE, COLOR_WHITE);
	// text
	init_pair(2, COLOR_YELLOW, -1);
	// cursor
	init_pair(3, COLOR_RED, COLOR_RED);

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
		showLastPressed(ch);
		showCurPos();
		// cursor
		attron(COLOR_PAIR(3));
		mvaddch(cursor.y, cursor.x, ' ');
		attroff(COLOR_PAIR(3));


		refresh();
		if (do_step) updateGrid(&grid);

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
	attron(COLOR_PAIR(2));
	mvprintw(0, 0, "Last Pressed: %c", lastc);
	attroff(COLOR_PAIR(2));
}

void showCurPos()
{
	attron(COLOR_PAIR(2));
	mvprintw(1, 0, "curpos: %i, %i", cursor.x, cursor.y);
	attroff(COLOR_PAIR(2));
}

void handleInput(char ch)
{
	switch (ch) {
		case 'q':
			running = false;
			break;
		case ' ':
			do_step ^= 1;
			break;
		case 'h':
			moveVect2i(&cursor, -1, 0);
			break;
		case 'j':
			moveVect2i(&cursor, 0, 1);
			break;
		case 'k':
			moveVect2i(&cursor, 0, -1);
			break;
		case 'l':
			moveVect2i(&cursor, 1, 0);
			break;
	}
	
}
