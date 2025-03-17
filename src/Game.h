#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <thread>
#include <functional>
#include <vector>

using namespace std;


namespace Game {
	extern GLFWwindow* window;
	int init(int w, int h);
	bool keyDown(int GLFWkey); //Is key held down
	void addCallbackToKeyDown(int GLFWkey, const function<void()>& func); //Calls passed in function when key is pressed
}

#endif