﻿
#define GLEW_STATIC

#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include<cmath>

namespace HelloTriangle {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f,  -0.5f, 0.0f,
		0.0f,   0.5f, 0.0f,
		//0.5f, -0.5f, 0.0f,
		//0.0f,  0.5f, 0.0f,
		0.8f,  0.8f, 0.0f,
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 1, 3
	};
	void processInput(GLFWwindow* window);

	const char* vertexShaderSource =
		"#version 330 core										 \n"
		"layout(location = 0) in vec3 aPos;						 \n"
		"void main(){											  \n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);	  \n"
		"}	  \n";

	const char* fragmentShaderSource =
		"#version 330 core										  \n"
		"out vec4 FragColor;									  \n"
		"void main(){											  \n"
		"	FragColor = vec4(1, 0, 0, 1);}			  \n";

	int Start() {

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(800, 600, "Hello OpenGL", NULL, NULL);
		if (window == NULL) {
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			glfwTerminate();
			return -1;
		}

		glViewport(0, 0, 800, 600);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//CULL BACK
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		while (!glfwWindowShouldClose(window))
		{
			//Input Event
			processInput(window);
			//Rendering Background
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(VAO);

			glUseProgram(shaderProgram);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			//glDrawArrays(GL_TRIANGLES, 0, 6);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwTerminate();
		return -1;
	}

	void processInput(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}
}
