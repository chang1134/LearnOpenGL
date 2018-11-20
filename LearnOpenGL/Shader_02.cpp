
#define GLEW_STATIC

#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include<cmath>
#include "Shader.h"
namespace Shader_02 {
	float vertices[] = {
		//left 3s is position, right 3s is color
		-0.5f, -0.5f, 0.0f, 1, 0, 0,
		0.5f,  -0.5f, 0.0f, 0, 1, 0,
		0.0f,   0.5f, 0.0f, 0, 0, 1,
		0.8f,   0.8f, 0.0f, 1, 0, 1,
		0.8f,   0.0f, 0.0f, 1, 1, 0
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 1, 3,
		1, 4, 3
	};
	 
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

		Shader* myShader = new Shader("vertexSource.txt", "fragmentSource.txt");

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

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		while (!glfwWindowShouldClose(window))
		{
			//Input Event
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, true);
			}
			//Rendering Background
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(VAO);

			myShader->use();

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			int vertexCount = sizeof(indices) / sizeof(indices[0]); //顶点数量，三角形的个数 * 3
			glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwTerminate();
		return -1;
	}

}