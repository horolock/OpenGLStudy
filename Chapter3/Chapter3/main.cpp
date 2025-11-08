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

const std::string vertFileName = "uniform-tri.vert";
const std::string fragFileName = "uniform-tri.frag";

const float step = 0.0005F;

GLuint vert = 0;
GLuint frag = 0;
GLuint prog = 0;

GLfloat vertPos[] = {
	-0.5F, 0.5F, 0.0F, 1.0F,
	-0.5F, -0.5F, 0.0F, 1.0F,
	+0.5F, -0.5F, 0.0F, 1.0F
};

GLfloat vertColor[] = {
	1.0F, 0.0F, 0.0F, 1.0F,
	0.0F, 1.0F, 0.0F, 1.0F,
	0.0F, 0.0F, 1.0F, 1.0F
};

GLfloat originMove[] = {
	0.0F, 0.0F, 0.0F, 0.0F
};

GLfloat currentMove[] = {
	0.0F, 0.0F, 0.0F, 0.0F
};

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

void updateFunc() {
	// Move X-axis 
	currentMove[0] += step;

	if (currentMove[0] >= 1.6F) {
		memcpy_s(currentMove, sizeof(currentMove), originMove, sizeof(originMove));
	}
}

void drawFunc() {
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint locPos = glGetAttribLocation(prog, "aPos");
	glEnableVertexAttribArray(locPos);
	glVertexAttribPointer(locPos, 4, GL_FLOAT, GL_FALSE, 0, vertPos);

	GLuint locColor = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(locColor);
	glVertexAttribPointer(locColor, 4, GL_FLOAT, GL_FALSE, 0, vertColor);

	GLuint locMove = glGetUniformLocation(prog, "uMove");
	glUniform4f(locMove, currentMove[0], currentMove[1], currentMove[2], currentMove[3]);
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
			memcpy_s(currentMove, sizeof(currentMove), originMove, sizeof(originMove));
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