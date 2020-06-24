#include <stdbool.h>

#ifndef GAME_H
#define GAME_H

void initGame();

bool isRunning();

void handleInput(char ch);

// Overlay
// Draws cursor and cursor position
void showCurPos();

bool endgame();

#endif
