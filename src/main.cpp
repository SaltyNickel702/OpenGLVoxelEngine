#include "Game.h"

int main () {
	thread renderLoop(Game::createWindow,600,800); //creates loop in a different thread

	//Run other things still necessary
	cout << "Hello World" << endl;

	renderLoop.join(); //wait until app is closed
	return 0;
}