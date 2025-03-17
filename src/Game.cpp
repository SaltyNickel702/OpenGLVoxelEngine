#include "Game.h"

using namespace Game;

//Private namespace
namespace {
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

	int init(int w, int h) {
		//Initialize
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //Set Version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Use core version of OpenGL
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); FOR MACOS


		//Create GLFW window
		window = glfwCreateWindow(w, h, "OpenGL Test", NULL, NULL); //Size, title, monitor, shared recourses
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



		//Shader Compilation + triangle test

		//Vertex Shader
		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		// check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//Fragment Shader
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\0";
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
		}

		//Link to Shader Program
		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram,vertexShader);
		glAttachShader(shaderProgram,fragmentShader);
		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if(!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << endl;
		}

		//delete shader programs
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);


		//Assign how to read vertex data
		//Triangle Verteces
		float vertices[] = {
			0.5f, 0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f
		};
		unsigned int indices[] = {
			0, 1, 2,
			1, 2, 3
		};

		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0); 

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0); 


		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//Render loop
		while(!glfwWindowShouldClose(window)) {
			processInput(window);

			//RENDERING
			glClearColor(.1f,.5f,.4f,1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
	
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	
			glfwSwapBuffers(window); //updates screen buffer
			glfwPollEvents(); //Check for inputs
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