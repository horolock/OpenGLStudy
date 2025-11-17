#define _USE_MATH_DEFINES
#include <cmath>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

#define GLM_FORCE_SWIZZLE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

#include "common.hpp"

const std::string vertFileName = "rotate-nz.vert";
const std::string fragFileName = "rotate-nz.frag";

GLuint vert = 0;
GLuint frag = 0;
GLuint prog = 0;

glm::vec4 vertPos[] = { // 5 vertices
	{ 0.0F, 0.5F, 0.0F, 1.0F }, // v0
	{ 0.5F, -0.3F, 0.0F, 1.0F }, // v1
	{ 0.0F, -0.3F, -0.5F, 1.0F }, // v2
	{ -0.5F, -0.3F, 0.0F, 1.0F }, // v3
	{ 0.0F, -0.3F, 0.5F, 1.0F }, // v4
};

glm::vec4 vertColor[] = { // 5 colors
	{ 1.0F, 1.0F, 1.0F, 1.0F, }, // v0: white
	{ 1.0F, 0.3F, 0.3F, 1.0F, }, // v1: red
	{ 0.3F, 1.0F, 0.3F, 1.0F, }, // v2: green
	{ 0.3F, 0.3F, 1.0F, 1.0F, }, // v3: blue
	{ 1.0F, 1.0F, 0.3F, 1.0F, }, // v4: yellow
};

GLuint indices[] = { // 6 * 3 = 18 indices
	0, 1, 2, // face 0: v0-v1-v2
	0, 2, 3, // face 1: v0-v2-v3
	0, 3, 4, // face 2: v0-v3-v4
	0, 4, 1, // face 3: v0-v4-v1
	1, 4, 3, // face 4: v1-v4-v3
	1, 3, 2, // face 5: v1-v3-v2
};

float theta = 0.0F;
system_clock::time_point lastTime = system_clock::now();


void initFunc(void) {
	const std::string vertSource = loadFile(vertFileName);
	const std::string fragSource = loadFile(fragFileName);

	const char* vertShader = vertSource.c_str();
	const char* fragShader = fragSource.c_str();

	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vertShader, nullptr);
	glCompileShader(vert);

	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fragShader, nullptr);
	glCompileShader(frag);

	// Program
	prog = glCreateProgram();
	glAttachShader(prog, vert);
	glAttachShader(prog, frag);

	glLinkProgram(prog);
	glValidateProgram(prog);

	glUseProgram(prog);
}

void updateFunc(void) {
	system_clock::time_point currentTime = system_clock::now();
	milliseconds elapsedTimeMSEC = duration_cast<milliseconds>(currentTime - lastTime);
	theta = (elapsedTimeMSEC.count() / 1000.0F) * (float)M_PI_2;
}

int cullMode = 0;

void drawFunc(void) {
	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0F, 1.0F);
	glClearDepthf(1.0F);

	switch (cullMode) {
	default:
	case 0:
		break;

	case 1:
		// Back-Face culling, CCW Facing
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		break;

	case 2:
		// Front-Face Culling, CCW Facing
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_FRONT);
		break;

	case 3:
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		break;

	case 4:
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_FRONT);
		break;
	}

	// Clear in gray color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Provide the vertex attributes
	GLuint locPos = glGetAttribLocation(prog, "aPos");
	glEnableVertexAttribArray(locPos);
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertPos[0]));

	GLuint locColor = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(locColor);
	glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertColor[0]));

	GLuint locTheta = glGetUniformLocation(prog, "uTheta");
	glUniform1f(locTheta, theta);

	// Draw the Pyramid
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, indices);

	// Done
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
	case GLFW_KEY_R:
		if (action == GLFW_PRESS) {
			lastTime = system_clock::now();
		}
		break;

	case GLFW_KEY_0:
		if (action == GLFW_PRESS) {
			cullMode = 0;
		}
		break;

	case GLFW_KEY_1:
		if (action == GLFW_PRESS) {
			cullMode = 1;
		}
		break;

	case GLFW_KEY_2:
		if (action == GLFW_PRESS) {
			cullMode = 2;
		}
		break;

	case GLFW_KEY_3:
		if (action == GLFW_PRESS) {
			cullMode = 3;
		}
		break;

	case GLFW_KEY_4:
		if (action == GLFW_PRESS) {
			cullMode = 4;
		}
		break;
	}
}

int main(int argc, char* argv[]) {
	glfwInit();
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(500, 500, "Rotation Pyramid", nullptr, nullptr);
	glfwSetWindowPos(window, 100, 100);
	glfwMakeContextCurrent(window);
	glewInit();

	// Prepare
	glfwSetWindowRefreshCallback(window, refreshFunc);
	glfwSetKeyCallback(window, keyFunc);
	glClearColor(0.5F, 0.5F, 0.5F, 1.0F);

	initFunc();

	while (!glfwWindowShouldClose(window)) {
		updateFunc();
		drawFunc();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}