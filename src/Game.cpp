#include "Game.h"

using namespace Game;

//Private namespace
namespace {
	void renderFrame () {
		processInput(window);

		glfwSwapBuffers(window); //updates screen buffer
		glfwPollEvents(); //Check for inputs
	}

	void windowResizeCallback(GLFWwindow* window, int width, int height) { //for when the window gets resized
		glViewport(0, 0, width, height);
	}

	//Input Handeling
	bool keysDown[GLFW_KEY_LAST-GLFW_KEY_SPACE];
	vector<function<void()>> functionCalls[GLFW_KEY_LAST-GLFW_KEY_SPACE];
	void processInput(GLFWwindow* window) {
		//esc key closes app (temporary)
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);


		//Adding/removing keys to keysDown | If new key is added, call callback functions
		for (int i = GLFW_KEY_SPACE; i < GLFW_KEY_LAST; i++) {
			bool isDown = keyDown(i);
			if (isDown) {
				bool previous = keysDown[i-33]; //
				if (!previous) {
					vector<function<void()>> funcs = functionCalls[i-33];
					for (const function<void()> func : funcs) {
						func();
					}
				}
				keysDown[i-33] = true;
			} else {
				keysDown[i-33] = false;
			}
		}
	}
}

//Exported Game namespace
namespace Game {
	GLFWwindow* window = nullptr;

	int createWindow(int w, int h) {
		//Initialize
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //Set Version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Use core version of OpenGL
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); FOR MACOS


		//Create GLFW window
		window = glfwCreateWindow(800, 600, "OpenGL Test", NULL, NULL); //Size, title, monitor, shared recourses
		if (window == NULL) {
			cout << "Failed to create GLFW window" << endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);


		//Initialize GLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			cout << "Failed to initialize GLAD" << endl;
			return -1;
		}

		//Sets GL Viewport (camera)
		glViewport(0, 0, w, h);
		glfwSetFramebufferSizeCallback(window,windowResizeCallback); //assigns callback function


		//Render loop
		while(!glfwWindowShouldClose(window)) {
			renderFrame();
		}
		glfwTerminate();

		return 0;
	}

	bool keyDown (int key) {
		return glfwGetKey(window, key) == GLFW_PRESS;
	}
	void addCallbackToKeyDown(int key, const function<void()>& func) {
		functionCalls[key-33].push_back(func);
	}
}