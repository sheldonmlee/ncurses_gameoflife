#include <ncurses.h>
#include "game.h"
#include "grid.h"
#include "vect.h"

static Grid* grid = 0;

static bool running = true;
static bool stepping_mode = false;
static bool do_step = true;
static Vect2i cursor;

// declaration of locally used
static void toggleStepMode();

static void toggleCell();

void initGame()
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
	
	grid = initGrid(width, height);
	//randomizeGrid(grid);
	cursor.x = width/2; cursor.y = height/2;
}

void updateGame()
{
	if (!grid) return;
	if (do_step) {
		updateGrid(grid);
		if (stepping_mode) do_step = false;
	}
}

void drawGame()
{
	if (!grid) return;
	drawGrid(grid);
}

bool isRunning() { return running; }


void handleInput(char ch)
{
	switch (ch) {
	case 'q':
		running = false;
		break;
	case ' ':
		toggleStepMode();
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
	case 'r':
		randomizeGrid(grid);
		break;
	case 'c':
		clearGrid(grid);
		break;
	case '\n':
		do_step = true;
		break;
	case 'i':
		toggleCell();
		break;
	default:
		if (ch != -1) do_step = true;
	}
}

void drawLastPressed(char ch)
{
	static char lastc = ' ';
	if (ch != -1) lastc = ch;
	attron(COLOR_PAIR(2));
	mvprintw(0, 0, "Last Pressed: %c", lastc);
	attroff(COLOR_PAIR(2));
}

void drawCurPos()
{
	attron(COLOR_PAIR(2));
	mvprintw(1, 0, "curpos: %i, %i", cursor.x, cursor.y);
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(3));
	mvaddch(cursor.y, cursor.x, ' ');
	attroff(COLOR_PAIR(3));
}

void endGame()
{
	// free stuff
	endwin();
	destroyGrid(grid);
}

// locally used
static void toggleStepMode()
{
	stepping_mode ^= 1;
	do_step = true;
}

static void toggleCell()
{
	if (!grid) return;
	bool cell = getPixel(grid, cursor.x, cursor.y);
	if (cell) setPixel(grid, cursor.x, cursor.y, 0);
	else setPixel(grid, cursor.x, cursor.y, 1);

}
