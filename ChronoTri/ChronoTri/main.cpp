#define _USE_MATH_DEFINES

#include <cmath>
#include <chrono>
#include <iostream>

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

const unsigned int WIN_W = 500;
const unsigned int WIN_H = 500;
const unsigned int WIN_X = 100;
const unsigned int WIN_Y = 100;

std::string vertFileName = "rotate.vert";
std::string fragFileName = "rotate.frag";

float theta = 0.0F;

GLuint vert = 0;
GLuint frag = 0;
GLuint prog = 0;

std::chrono::system_clock::time_point lastTime = std::chrono::system_clock::now();

glm::vec4 vertPos[3] = {
	{ -0.5F, -0.5F, 0.0F, 1.0F, },
	{ +0.5F, -0.5F, 0.0F, 1.0F, },
	{ -0.5F, +0.5F, 0.0F, 1.0F, },
};

glm::vec4 vertColor[] = {
	{ 1.0F, 0.0F, 0.0F, 1.0F, },
	{ 0.0F, 1.0F, 0.0F, 1.0F, },
	{ 0.0F, 0.0F, 1.0F, 1.0F, },
};

void initFunc(void) {
	std::string vertSource = loadFile(vertFileName);
	std::string fragSource = loadFile(fragFileName);
	char buf[1024];
	GLint status;

	// Vert
	const char* vertShader = vertSource.c_str();
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vertShader, nullptr);
	glCompileShader(vert);
	glGetShaderiv(vert, GL_COMPILE_STATUS, &status);

	std::cout << "Vert Compile = " << ((status == GL_TRUE) ? "true" : "false") << std::endl;
	
	glGetShaderInfoLog(vert, sizeof(buf), nullptr, buf);

	std::cout << "Vert Log [" << buf << "]" << std::endl;

	// Frag
	const char* fragShader = fragSource.c_str();
	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fragShader, nullptr);
	glCompileShader(frag);
	glGetShaderiv(frag, GL_COMPILE_STATUS, &status);

	std::cout << "Frag Compile = " << ((status == GL_TRUE) ? "true" : "false") << std::endl;
	glGetShaderInfoLog(frag, sizeof(buf), nullptr, buf);
	std::cout << "Frag Log [" << buf << "]" << std::endl;

	// Program
	prog = glCreateProgram();
	glAttachShader(prog, vert);
	glAttachShader(prog, frag);
	glLinkProgram(prog);

	glGetProgramiv(prog, GL_LINK_STATUS, &status);

	std::cout << "Prog Link Status = " << ((status == GL_TRUE) ? "true" : "false") << std::endl;
	glGetProgramInfoLog(prog, sizeof(buf), nullptr, buf);
	std::cout << "Link Log [" << buf << "]" << std::endl;

	glValidateProgram(prog);

	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);

	std::cout << "Prog Validate Status = " << ((status == GL_TRUE) ? "true" : "false") << std::endl;
	glGetProgramInfoLog(prog, sizeof(buf), nullptr, buf);
	std::cout << "Validate Log [" << buf << "]" << std::endl;

	glUseProgram(prog);
}

void updateFunc() {
	std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
	std::chrono::milliseconds elapsedTimeMSEC = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime);
	theta = (elapsedTimeMSEC.count() / 1000.0F) * (float)M_PI_2;
}

void drawFunc() {
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint locPos = glGetAttribLocation(prog, "aPos");
	glEnableVertexAttribArray(locPos);
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertPos[0]));

	GLuint locColor = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(locColor);
	glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertColor[0]));

	// Draw the triangle
	GLuint locTheta = glGetUniformLocation(prog, "uTheta");
	glUniform1f(locTheta, theta);
	glDrawArrays(GL_TRIANGLES, 0, 3);

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
			lastTime = std::chrono::system_clock::now();
		}
		break;
	}
}

int main(int argc, char* argv[]) {
	glfwInit();
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, "Chrono Timer", nullptr, nullptr);
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
		// Animate Loop
		updateFunc();
		drawFunc();

		// GLFW Actions
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}