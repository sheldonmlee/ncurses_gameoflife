#ifndef UI_H
#define UI_H

#define ui_type uint8_t

#define UI_NULL 0
#define UI_INT 1
#define UI_FLOAT 2
#define UI_CHAR 3
#define UI_STRING 4

//void startUI();

void addLine(char* msg, void* var, int size, ui_type type);

void drawUI();

void endUI();

#endif
