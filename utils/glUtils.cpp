#include "glUtils.h"
#include "../DebugLib/DebugSymb.h"
#include "../DebugLib/GL_Debug.h"
#include <GLFW/glfw3.h>
#include <fstream>

constexpr int maxLineSize = 1024;

#define numVAOs 1

//GLuint renderingProgram;
//GLuint vao[numVAOs];

std::string loadShader(std::string_view fileName)
{
	std::fstream file(fileName.data());
	if (!file.is_open()) {
		DebugNS::rDebug(3) << "Can not open shader file: " << fileName.data() << std::endl;
	}
	
	std::string result;
	result.reserve(maxLineSize);
	char line[maxLineSize / 8];

	while (!file.eof()) {
		file.getline(line, maxLineSize);
		result += line;
		result += "\n";
	}

	return result;
}

GLuint createShaderProgram()
{
	std::string vshaderSource = loadShader("VertexShader.txt");

	std::string fshaderSource = loadShader("FragmentShader.txt");

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vs = vshaderSource.c_str();
	const char* fs = fshaderSource.c_str();

	glShaderSource(vShader, 1, &vs, NULL);
	glShaderSource(fShader, 1, &fs, NULL);

	glCompileShader(vShader);
	GLDebug::printShaderLog(vShader);

	glCompileShader(fShader);
	GLDebug::printShaderLog(fShader);

	GLuint vfProgram = glCreateProgram();

	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);

	GLDebug::checkOpenGLError();

	glLinkProgram(vfProgram);
	GLDebug::printProgramLog(vfProgram);

	return vfProgram;
}

/*
void GLinit(GLFWwindow* window)
{
	renderingProgram = createShaderProgram();

	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}

float x = 0.0f; // location of triangle on x axis
float inc = 0.01f;

static void display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT); // clear the background to black, each time

	glUseProgram(renderingProgram);

	x += inc; // move the triangle along x axis
	if (x > 1.0f) inc = -0.01f;
	if (x < -1.0f) inc = 0.01f; // switch to moving the triangle to the right

	GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset"); // get ptr to "offset"

	glProgramUniform1f(renderingProgram, offsetLoc, x);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}
*/