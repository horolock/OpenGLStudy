#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common.hpp"

const unsigned int WIN_W = 500;
const unsigned int WIN_H = 500;

const unsigned int WIN_X = 100;
const unsigned int WIN_Y = 100;

const std::string vertFileName = "uniform-tri.vert";
const std::string fragFileName = "uniform-tri.frag";

const float step = 0.0005F;

GLuint vert = 0;
GLuint frag = 0;
GLuint prog = 0;

// MARK: - Rotation Related
float theta = 0.0F;
const float thetaStep = 0.01F;

glm::vec4 vertPos[] = {
	{-0.5F, +0.5F, 0.0F, 1.0F},
	{-0.5F, -0.5F, 0.0F, 1.0F},
	{+0.5F, -0.5F, 0.0F, 1.0F},
};

glm::vec4 rotatePos[3];

glm::vec4 vertColor[] = {
	{1.0F, 0.0F, 0.0F, 1.0F},
	{0.0F, 1.0F, 0.0F, 1.0F},
	{0.0F, 0.0F, 1.0F, 1.0F},
};

const glm::vec4 originMove = glm::vec4(0.0F, 0.0F, 0.0F, 0.0F);
glm::vec4 currentMove = glm::vec4(0.0F, 0.0F, 0.0F, 0.0F);

void initFunc() {
	std::string vertSource = loadFile(vertFileName);
	std::string fragSource = loadFile(fragFileName);

	char buf[1024];
	GLint status;

	const char* vertShader = vertSource.c_str();
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vertShader, NULL);
	glCompileShader(vert);
	glGetShaderiv(vert, GL_COMPILE_STATUS, &status);
	std::cout << "Vert Compile Status = " << ((status == GL_TRUE) ? "true" : "false") << std::endl;
	glGetShaderInfoLog(vert, sizeof(buf), NULL, buf);
	std::cout << "Vert Shader Log [" << buf << "]\n";

	// Frag
	const char* fragShader = fragSource.c_str();
	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fragShader, NULL);
	glCompileShader(frag);
	glGetShaderiv(frag, GL_COMPILE_STATUS, &status);
	std::cout << "Frag Compile Status = " << ((status == GL_TRUE) ? "true" : "false") << std::endl;
	glGetShaderInfoLog(frag, sizeof(buf), NULL, buf);
	std::cout << "Frag Shader Log [" << buf << "]\n";

	// Program
	prog = glCreateProgram();
	glAttachShader(prog, vert);
	glAttachShader(prog, frag);
	glLinkProgram(prog);

	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	std::cout << "Program Link Status = " << ((status == GL_TRUE) ? "true" : "false") << std::endl;
	
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	std::cout << "Program Info Log [" << buf << "]\n";

	glValidateProgram(prog);
	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	std::cout << "Program Validate Status = " << ((status == GL_TRUE) ? "true" : "false") << std::endl;
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	std::cout << "Program Valid Info Log [" << buf << "]\n";

	glUseProgram(prog);
}

void rotateFunc() {
	theta += thetaStep;

	/*for (int i = 0; i < 3; i++) {
		rotatePos[i].x = vertPos[i].x * cosf(theta) - vertPos[i].y * sinf(theta);
		rotatePos[i].y = vertPos[i].x * sinf(theta) + vertPos[i].y * cosf(theta);
		rotatePos[i].z = vertPos[i].z;
		rotatePos[i].w = vertPos[i].w;
	}*/
}

void moveXFunc() {
	// Move X-axis 
	currentMove.x += step;

	if (currentMove[0] >= 1.6F) {
		currentMove = originMove;
	}
}

void updateFunc() {
	rotateFunc();
}

void drawFunc() {
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint locPos = glGetAttribLocation(prog, "aPos");
	glEnableVertexAttribArray(locPos);
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertPos[0]));
	//glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(rotatePos[0]));

	GLuint locColor = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(locColor);
	glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, glm::value_ptr(vertColor[0]));

	GLuint locMove = glGetUniformLocation(prog, "uMove");
	glUniform4fv(locMove, 1, glm::value_ptr(currentMove));

	GLuint locTheta = glGetUniformLocation(prog, "uTheta");
	glUniform1f(locTheta, theta);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glFinish();
}

void refreshFunc(GLFWwindow* window) {
	drawFunc();

	glfwSwapBuffers(window);
}

void keyFunc(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		break;
	case GLFW_KEY_R:
		if (action == GLFW_PRESS) {
			currentMove = originMove;
			theta = 0;
		}
		break;
	}
}


int main(int argc, char* argv[]) {
	glfwInit();
	//glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, "Animated Triangle", NULL, NULL);
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
		updateFunc();
		drawFunc();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Done
	glfwTerminate();

	return 0;
}