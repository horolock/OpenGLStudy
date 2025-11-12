
#include <iostream>

using namespace std;

#define GLM_FORCE_SWIZZLE

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

const std::string vertFileName = "colored-tri.vert";
const std::string fragFileName = "colored-tri.frag";

GLuint vert = 0;
GLuint frag = 0;
GLuint prog = 0;

glm::vec4 vertPos[] = { // 6 * 3 = 18 vertices
	// face 0: v0-v1-v2
	{ 0.0F, 0.5F, 0.0F, 1.0F }, // v0
	{ 0.5F, -0.3F, 0.0F, 1.0F }, // v1
	{ 0.0F, -0.3F, 0.5F, 1.0F }, // v2
	// face 1: v0-v2-v3
	{ 0.0F, 0.5F, 0.0F, 1.0F }, // v0
	{ 0.0F, -0.3F, 0.5F, 1.0F }, // v2
	{ -0.5F, -0.3F, 0.0F, 1.0F }, // v3
	// face 2: v0-v3-v4
	{ 0.0F, 0.5F, 0.0F, 1.0F }, // v0
	{ -0.5F, -0.3F, 0.0F, 1.0F }, // v3
	{ 0.0F, -0.3F, -0.5F, 1.0F }, // v4
	// face 3: v0-v4-v1
	{ 0.0F, 0.5F, 0.0F, 1.0F }, // v0
	{ 0.0F, -0.3F, -0.5F, 1.0F }, // v4
	{ 0.5F, -0.3F, 0.0F, 1.0F }, // v1
	// face 4: v1-v4-v3
	{ 0.5F, -0.3F, 0.0F, 1.0F }, // v1
	{ 0.0F, -0.3F, -0.5F, 1.0F }, // v4
	{ -0.5F, -0.3F, 0.0F, 1.0F }, // v3
	// face 5: v1-v3-v2
	{ 0.5F, -0.3F, 0.0F, 1.0F }, // v1
	{ -0.5F, -0.3F, 0.0F, 1.0F }, // v3
	{ 0.0F, -0.3F, 0.5F, 1.0F }, // v2
};

glm::vec4 vertColor[] = {
	// face 0: red
	{ 1.0F, 0.3F, 0.3F, 1.0F, },
	{ 1.0F, 0.3F, 0.3F, 1.0F, },
	{ 1.0F, 0.3F, 0.3F, 1.0F, },
	// face 1: green
	{ 0.3F, 1.0F, 0.3F, 1.0F, },
	{ 0.3F, 1.0F, 0.3F, 1.0F, },
	{ 0.3F, 1.0F, 0.3F, 1.0F, },
	// face 2: blue
	{ 0.3F, 0.3F, 1.0F, 1.0F, },
	{ 0.3F, 0.3F, 1.0F, 1.0F, },
	{ 0.3F, 0.3F, 1.0F, 1.0F, },
	// face 3: yellow
	{ 1.0F, 1.0F, 0.3F, 1.0F, },
	{ 1.0F, 1.0F, 0.3F, 1.0F, },
	{ 1.0F, 1.0F, 0.3F, 1.0F, },
	// face 4: cyan
	{ 0.3F, 1.0F, 1.0F, 1.0F, },
	{ 0.3F, 1.0F, 1.0F, 1.0F, },
	{ 0.3F, 1.0F, 1.0F, 1.0F, },
	// face 5: cyan
	{ 0.3F, 1.0F, 1.0F, 1.0F, },
	{ 0.3F, 1.0F, 1.0F, 1.0F, },
	{ 0.3F, 1.0F, 1.0F, 1.0F, },
};

void initFunc(void) {
	const char* vertSource = loadFile(vertFileName).c_str();
	const char* fragSource = loadFile(fragFileName).c_str();
	char buf[1024];
	GLint status;


}