#include <stdlib.h>
#include "grid.h"

void initGrid(Grid* grid, unsigned int width, unsigned int height)
{
	grid->size = width*height;
	grid->width = width;
	grid->arr = (bool*)malloc(sizeof(bool)*grid->size);
}

// maps x, y coordinate to array index of grid
unsigned int toIndex(Grid* grid, int x, int y)
{
	return (grid->width*y + x)%grid->size;
}

void clearGrid(Grid* grid)
{
	for (int i = 0; i < grid->size; i++) grid->arr[i]=false;
}

void updateGrid(Grid* grid)
{
	unsigned int width = grid->width;
	unsigned int height = grid->size/width;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

		}
	}
}

void putPixel(Grid* grid, int x, int y)
{
	grid->arr[toIndex(grid, x, y)] = true;
}

void drawGrid(Grid* grid)
{
	unsigned int width, height;
	width = grid->width;
	height = grid->size/width;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (grid->arr[toIndex(grid, x, y)]) mvprintw(y, x, "x");
			else mvprintw(y, x, " ");
		}
	}
}
