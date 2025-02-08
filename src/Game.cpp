#include "Game.h"

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


		//render loop
		while(!glfwWindowShouldClose(window)) {
			glfwSwapBuffers(window); //reboots screen buffer
			glfwPollEvents(); //Check for inputs
		}

		glfwTerminate();
		return 0;
	}
	void windowResizeCallback(GLFWwindow* window, int width, int height) { //for when the window gets resized
		glViewport(0, 0, width, height);
	};
}