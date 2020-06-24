#include <ncurses.h>
#include "game.h"
#include "grid.h"
#include "vect.h"

static Grid* grid = 0;

static bool running = true;
static bool do_step = true;
static Vect2i cursor;

void initGame()
{
	int width = 0;
	int height = 0;
	// stdscr is screen created by initscr()
	getmaxyx(stdscr, height, width);

	initGrid(grid, height, width);
	randomizeGrid(grid);
	cursor.x = width/2; cursor.y = height/2;
}

static void step() { do_step ^= 1; }

void updateGame()
{
	if (!grid) return;
	if (do_step) updateGrid(grid);
}

void drawGame()
{
	if (!grid) return;
	drawGrid(grid);
	refresh();
}

bool isRunning() { return running; }

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
	case 's':
		step();
		break;
	}
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
	attron(COLOR_PAIR(3));
	mvaddch(cursor.y, cursor.x, ' ');
	attroff(COLOR_PAIR(3));
	attroff(COLOR_PAIR(2));
}

void endGame()
{
}
