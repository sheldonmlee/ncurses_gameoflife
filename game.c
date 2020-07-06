#include <ncurses.h>
#include <stdlib.h>
#include "game.h"
#include "grid.h"
#include "vect.h"
#include "log.h"

static Grid* grid = 0;

static bool running = true;
static bool stepping_mode = false;
static bool do_step = true;
static Vect2i cursor;

// declaration of locally used
static void toggleStepMode();

static void toggleCell();

int min (int a, int b);

int max (int a, int b);

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
	// {{{ movement
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
	case 'H':
		moveVect2i(&cursor, -10, 0);
		break;
	case 'J':
		moveVect2i(&cursor, 0, 10);
		break;
	case 'K':
		moveVect2i(&cursor, 0, -10);
		break;
	case 'L':
		moveVect2i(&cursor, 10, 0);
		break;
	// }}}
	// {{{ Cell
	case 'r':
		randomizeGrid(grid);
		break;
	case 'c':
		clearGrid(grid);
		break;
	case 'i':
		toggleCell();
		break;
	// }}}
	// {{{ game load/save
	case 'e':
		loadGame("test.txt");
		break;
	case 'w':
		saveGame("test.txt");
		break;
	// }}}
	// {{{ flow
	case 'q':
		running = false;
		break;
	case ' ':
		toggleStepMode();
		break;
	default:
		if (ch != -1) do_step = true;
	// }}}
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

void saveGame(char* name)
{
	FILE* file = NULL;
	file = fopen(name, "w");
	if (!file) {
		logLine("Failed to write file.");
		return;
	}
	
	unsigned int dimensions[2] = {grid->width, grid->size};
	fwrite(dimensions, sizeof(dimensions), 1, file);
	fwrite(grid->state, sizeof(bool), grid->size, file);

	fclose(file);
}

void loadGame(char* name)
{
	FILE* file = NULL;
	file = fopen(name, "r");
	if (!file) {
		logLine("Failed to load file.");
		return;
	}
	
	if (!grid) initGame();
	else clearGrid(grid);
	
	unsigned int width, height, size;
	bool* pixels;

	// read data frrom file
	fread(&width, sizeof(unsigned int), 1, file);
	fread(&size, sizeof(unsigned int), 1, file);
	height = size/width;
	pixels = (bool*)malloc(sizeof(bool)*size);
	fread(pixels, sizeof(bool), size, file);

	unsigned int grid_width, grid_height;

	// map & copy new pixels array to current grid
	getDimensions(grid, &grid_width, &grid_height);
	for (int y =0; y < min(grid_height, height); y++) {
		for (int x =0; x < min(grid_width, width); x++) {
			int index = y * width + x;
			setPixel(grid, x, y, pixels[index]);
		}
	}
	free(pixels);
		
	fclose(file);
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

int min(int a, int b)
{
	if (a <= b) return a;
	else return b;
}

int max(int a, int b)
{
	if (a >= b) return a;
	else return b;
}
