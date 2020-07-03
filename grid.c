#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
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

static void contain(int* num, int min, int max)
{
	int delta = max - min;
	while (true) {
		if (*num < min) *num += delta;
		else if (*num >= max) *num -= delta;
		else break;
	}
}
// maps x, y coordinate to array index of grid
unsigned int toIndex(Grid* grid, int x, int y)
{
	unsigned int width, height;
	getDimensions(grid, &width, &height);
	contain(&x, 0, width);
	contain(&y, 0, height);
	return (grid->width*y + x);
}

bool getPixel(Grid* grid, int x, int y)
{
	return grid->state[toIndex(grid, x, y)];
}

void getDimensions(Grid* grid, unsigned int* width, unsigned int* height)
{
	*width = grid->width;
	*height = grid->size/grid->width;
}

void clearGrid(Grid* grid)
{
	for (int i = 0; i < grid->size; i++) grid->state[i]=false;
}

void updateGrid(Grid* grid)
{
	unsigned int width, height;
	getDimensions(grid, &width, &height);
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
	getDimensions(grid, &width, &height);
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

void destroyGrid(Grid* grid)
{
	free(grid->state);
	free(grid->next_state);
	free(grid);
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

