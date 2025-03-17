#include "Game.h"

int main () {
	thread renderLoop(Game::init,800,600); //creates loop in a different thread

	//Run other things still necessary
	cout << "Hello World" << endl;

	renderLoop.join(); //wait until app is closed
	return 0;
}