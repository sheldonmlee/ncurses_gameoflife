#include <stdio.h>
#include "log.h"
static FILE* file = 0;
static char* name;

void startLog(char* filename)
{
	name = filename;
	file = fopen(filename, "w");
}

void logString(char* string)
{
	if (!file) return;
	fputs(string, file);
}

void logLine(char* string)
{
	if (!file) return;
	fputs(string, file);
	fputs("\n", file);
}

void endLog()
{
	if (!file) return;
	fclose(file);
}
