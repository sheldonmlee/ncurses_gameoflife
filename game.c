#include "game.h"
#include "grid.h"
#include "vect.h"

static Grid grid;

static bool running = true;
static bool do_step = true;
static Vect2i cursor = {0, 0};

void initGame()
{
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
	}
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
