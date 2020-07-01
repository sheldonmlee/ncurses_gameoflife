#include <stdio.h>
#include <ncurses.h>
// Delay and timing.
#include <unistd.h>
#include <time.h>
// math
#include <math.h>
// game
#include "game.h"
#include "log.h"


int main()
{ 

	// framerate of the game 
	const int FRAME_RATE = 30;
	const float FRAME_TIME = 1.f/(float)FRAME_RATE;
	startLog("log.txt");

	initGame();

	float t = 0;
	while (isRunning()) {
		clock_t start_t = clock();
		char ch = getch();

		handleInput(ch);

		drawGame();
		drawLastPressed(ch);
		drawCurPos();

		refresh();
		
		updateGame();

		usleep(pow(10,6)*(FRAME_TIME-t));
		float t = (float) (clock()-start_t) / (float) CLOCKS_PER_SEC;

	}

	endGame();
	endLog();
	return 0;
}

