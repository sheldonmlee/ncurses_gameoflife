#include <stdbool.h>

#ifndef GAME_H
#define GAME_H

void initGame();

bool isRunning();

void updateGame();

void drawGame();

void handleInput(char ch);

// Overlays
// Draws cursor and cursor position
void drawLastPressed(char ch);

void drawCurPos();

void saveGame(char* name);

void loadGame(char* name);

void endGame();

#endif

