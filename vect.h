#ifndef VECT_H
#define VECT_H

typedef struct Vect2i{
	int x, y;
} Vect2i;

typedef struct Vect2f{
	float x, y;
} Vect2f;

void moveVect2i(Vect2i* vect, int x, int y);

void moveVect2f(Vect2f* vect, float x, float y);

#endif
