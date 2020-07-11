#include <stddef.h>
#include <stdlib.h>
#include <ncurses.h>
#include "ui.h"

typedef struct {
	char* msg;
	void* var;
	size_t size;
	ui_type type;

}Linei;

static unsigned int ln_count = 0;

static Linei* lines = NULL;

static void startUI();

void addLinei(char* msg, void* var, int size, ui_type type) 
{
	if (!lines) startUI();
	else lines = realloc(lines, sizeof(Linei) * ++ln_count);
	Linei line = { msg, var };
	lines[ln_count-1] = line; 
}

void drawUI()
{
	if (!lines) return;
	attron(COLOR_PAIR(2));
	for (int i = 0; i < ln_count; i++) {
		mvprintw(i, 0, "%s %i", lines[i].msg, *lines[i].var);
	}
	attroff(COLOR_PAIR(2));
}

void endUI()
{
	free(lines);
}

static void startUI()
{
	lines = (Linei*)malloc(sizeof(Linei) * ++ln_count);
}
