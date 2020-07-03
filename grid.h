#include <stdbool.h>

#ifndef GRID_H
#define GRID_H

typedef struct Grid {
	unsigned int size;
	unsigned int width;
	bool* state;
	bool* next_state;
} Grid;

// inits grid and returns pointer to grid. Remember to use Destroy Grid to deallocate
Grid* initGrid(unsigned int width, unsigned int height);

void randomizeGrid(Grid* grid);

unsigned int toIndex(Grid* grid, int x, int y);

bool getPixel(Grid* grid, int x, int y);

void getDimensions(Grid* grid, unsigned int* width, unsigned int* height);

void clearGrid(Grid* grid);

void updateGrid(Grid* grid);

void setPixel(Grid* grid, int x, int y, bool on);

void drawGrid(Grid* grid);

void destroyGrid(Grid* grid);

#endif

