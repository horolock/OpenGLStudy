#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")

#pragma comment(lib, "glfw3.lib")

#include <stdio.h>

const unsigned int WIN_W = 300;
const unsigned int WIN_H = 300;
const unsigned int WIN_X = 100;
const unsigned int WIN_Y = 100;

void refreshFunc(GLFWwindow* window) {
	// Refresh
	printf("refresh called\n");
	fflush(stdout);
	glClear(GL_COLOR_BUFFER_BIT);
	glFinish();

	glfwSwapBuffers(window);
}

void keyFunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		break;
	}
}

int main(void) {
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, "Hello GLFW", NULL, NULL);
	glfwSetWindowPos(window, WIN_X, WIN_Y);

	glfwMakeContextCurrent(window);

	// Start GLEW
	glewInit();

	// MARK: - Prepare
	glfwSetWindowRefreshCallback(window, refreshFunc);
	glfwSetKeyCallback(window, keyFunc);
	glClearColor(0.5F, 0.8F, 0.8F, 1.0F);

	// Main Loop
	while (!glfwWindowShouldClose(window)) {
		// Draw
		glClear(GL_COLOR_BUFFER_BIT);
		glFinish();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}