#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "grid.h"

// locally used declaration
static bool isAliveNext(Grid* grid, int x, int y);

Grid* initGrid(unsigned int width, unsigned int height)
{
	Grid* grid = (Grid*)malloc(sizeof(Grid));
	grid->size = width*height;
	grid->width = width;
	grid->state = (bool*)malloc(sizeof(bool)*grid->size);
	grid->next_state = (bool*)malloc(sizeof(bool)*grid->size);
	return grid;
}

void randomizeGrid(Grid* grid)
{
	srand(time(NULL));
	for (int i = 0; i < grid->size; i++) {
		grid->state[i] = rand()%2;
	}
}
// maps x, y coordinate to array index of grid
unsigned int toIndex(Grid* grid, int x, int y)
{
	return (grid->width*y + x)%grid->size;
}

bool getPixel(Grid* grid, int x, int y)
{
	return grid->state[toIndex(grid, x, y)];
}

void clearGrid(Grid* grid)
{
	for (int i = 0; i < grid->size; i++) grid->state[i]=false;
}

void updateGrid(Grid* grid)
{
	unsigned int width = grid->width;
	unsigned int height = grid->size/width;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			grid->next_state[toIndex(grid, x, y)] = isAliveNext(grid, x, y);
		}
	}

	for (int i = 0; i < grid->size; i++) {
		grid->state[i] = grid->next_state[i];
	}
}

void setPixel(Grid* grid, int x, int y, bool on)
{
	grid->state[toIndex(grid, x, y)] = on;
}

void drawGrid(Grid* grid)
{
	unsigned int width, height;
	width = grid->width;
	height = grid->size/width;
	// Init color pair init_pair(index, fg, bg);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (grid->state[toIndex(grid, x, y)]){
				attron(COLOR_PAIR(1));
				mvaddch(y, x, ' ');
				attroff(COLOR_PAIR(1));
			}
			else mvaddch(y, x, ' ');
		}
	}
}

// locally used
// check if cell's next state is alive
static bool isAliveNext(Grid* grid, int x, int y)
{
	bool nw	= getPixel(grid, x-1, y-1);
	bool n 	= getPixel(grid, x, y-1);
	bool ne	= getPixel(grid, x+1, y-1);
	bool w	= getPixel(grid, x-1, y);
	bool e	= getPixel(grid, x+1, y);
	bool sw	= getPixel(grid, x-1, y+1);
	bool s	= getPixel(grid, x, y+1);
	bool se	= getPixel(grid, x+1, y+1);

	bool currentlyAlive = grid->state[toIndex(grid, x, y)];

	const int no_neighbors = 8;
	bool neighbors[] = {
		nw,	n,	ne,
		w,		e,
		sw,	s,	se
	};

	int alive_neighbors = 0;
	for (int i = 0; i < no_neighbors; i++) {
		alive_neighbors += neighbors[i];
	}
	// rules
	if (currentlyAlive) {
		if (alive_neighbors == 2 || alive_neighbors == 3) {
			return true;
		}
	}
	else if (alive_neighbors == 3) {
		return true;
	}
	return false;
}

