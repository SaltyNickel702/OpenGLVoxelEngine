#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>


using namespace std;

namespace Game {
	extern GLFWwindow* window;
	int createWindow(int w, int h);
	void windowResizeCallback(GLFWwindow* window, int width, int height);
}

#endif