#include "Game.h"

int main () {
	int createWin = Game::createWindow(600,800);
	if (createWin == -1) return -1; //pass on error termination from creation function

	return 0;
}