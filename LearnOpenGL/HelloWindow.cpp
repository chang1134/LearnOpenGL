#define GLEW_STATIC

#include<GL\glew.h>
#include<GLFW\glfw3.h>
 
namespace HelloWindow {

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

		while (!glfwWindowShouldClose(window))
		{
			//Input Event
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, true);
			}
			//Rendering Background
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwTerminate();
		return -1;
	}
}

