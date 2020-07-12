#include <stddef.h>
#include <stdlib.h>
#include <ncurses.h>
#include "ui.h"
#include "log.h"

typedef struct {
	char* msg;
	void* var;
	size_t size;
	ui_type type;

}Line;

static unsigned int ln_count = 0;

static Line* lines = NULL;

// declaration of locally used 
static void startUI();

static void drawLine(Line*, int offset);

void addLine(char* msg, void* var, int size, ui_type type) 
{
	if (!lines) startUI();
	else lines = realloc(lines, sizeof(Line) * ++ln_count);
	Line line = { msg, var, size, type};
	lines[ln_count-1] = line; 
}

void drawUI()
{
	if (!lines) return;
	attron(COLOR_PAIR(2));
	
	for (int i = 0; i < ln_count; i++) {
		drawLine(&lines[i], i);
	}
	attroff(COLOR_PAIR(2));
}

void endUI()
{
	free(lines);
}

// static definition
static void startUI()
{
	lines = (Line*)malloc(sizeof(Line) * ++ln_count);
}

static void drawLine(Line* line, int offset)
{
	switch (line->type) {
	case UI_INT:
		mvprintw(offset, 0, "%s %i", line->msg, *((int*)line->var) );
		break;
	case UI_FLOAT:
		mvprintw(offset, 0, "%s %f", line->msg, *((float*)line->var) );
		break;
	case UI_CHAR:
		mvprintw(offset, 0, "%s %c", line->msg, *((char*)line->var) );
		break;
	case UI_STRING:
		mvprintw(offset, 0, "%s %s", line->msg, ((char*)line->var) );
		break;
	}
}
