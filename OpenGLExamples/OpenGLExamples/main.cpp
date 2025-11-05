
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

#include "common.hpp"


const unsigned int WIN_W = 500;
const unsigned int WIN_H = 500;
const unsigned int WIN_X = 100;
const unsigned int WIN_Y = 100;

const std::string vertFileName = "simple-tri.vert";
const std::string fragFileName = "simple-tri.frag";

GLuint vert = 0;
GLuint frag = 0;
GLuint prog = 0;

GLfloat vertexPos[] = {
	-0.5F, -0.5F, 0.0F, 1.0F,
	+0.5F, -0.5F, 0.0F, 1.0F,
	-0.5F, +0.5F, 0.0F, 1.0F,
};

void initFunc(void) {
	const std::string vertSource = loadFile(vertFileName);
	const std::string fragSource = loadFile(fragFileName);

	// Vertex Shader
	const char* vertSourcePtr = vertSource.c_str();
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vertSourcePtr, NULL);
	glCompileShader(vert);

	// Fragment Shader
	const char* fragSourcePtr = fragSource.c_str();
	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fragSourcePtr, NULL);
	glCompileShader(frag);

	// Program
	prog = glCreateProgram();
	glAttachShader(prog, vert);
	glAttachShader(prog, frag);
	glLinkProgram(prog);

	// Execute
	glUseProgram(prog);
}

void drawFunc(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	GLuint loc = glGetAttribLocation(prog, "vertexPos");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertexPos);

	// Draw Triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glFinish();
}

void refreshFunc(GLFWwindow* window) {
	drawFunc();
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

int main(int argc, char* argv[]) {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, "OpenGL Example", NULL, NULL);
	glfwSetWindowPos(window, WIN_X, WIN_Y);
	glfwMakeContextCurrent(window);
	glewInit();

	// Prepare
	glfwSetWindowRefreshCallback(window, refreshFunc);
	glfwSetKeyCallback(window, keyFunc);
	glClearColor(0.5F, 0.5F, 0.5F, 1.0F);

	// Main Loop
	initFunc();

	while (!glfwWindowShouldClose(window)) {
		// Draw
		drawFunc();

		// GLFW Actions
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}