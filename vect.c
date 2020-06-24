#include "vect.h"

void moveVect2i(Vect2i* vect, int x, int y)
{
	vect->x += x;
	vect->y += y;
}


void moveVect2f(Vect2f* vect, float x, float y)
{
	vect->x += x;
	vect->y += y;
}

