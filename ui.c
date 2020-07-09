#include <stddef.h>
#include <stdlib.h>
#include "ui.h"

typedef struct {
	char* msg;
	int* var;
}Linei;

static unsigned int ln_count = 0;

static Linei* lines = NULL;

void initUI()
{
	lines = (Linei*)malloc(sizeof(Linei) * ++ln_count);
}

void addLinei(char* msg, int* var)
{
	if (!lines) return;
	if (ln_count >1) lines = realloc(lines, sizeof(Linei) * ++ln_count);
	Linei line = { msg, var };
	lines[ln_count-1] = line; 
}

void drawUI()
{
}

