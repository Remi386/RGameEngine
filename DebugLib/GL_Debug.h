#pragma once

#include <GL/glew.h>
#include "DebugOut.h"

#ifdef DEBUG_BUILD

namespace GLDebug {

	inline void printShaderLog(GLuint shader)
	{
		GLint vertCompiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &vertCompiled);

		if (vertCompiled != 1) {
			DebugNS::rDebug(1) << "shader compilation failed (id = " << shader << ") " << std::endl;

			int len = 0;

			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			if (len > 0) {
				int charsWritten;
				char* log = new char[len];

				glGetShaderInfoLog(shader, len, &charsWritten, log);
				DebugNS::rDebug(1) << "Shader Info Log: " << log << std::endl;

				delete[] log;
			}
		}
	}

	inline void printProgramLog(GLuint prog)
	{
		GLint linked;
		glLinkProgram(prog);

		glGetProgramiv(prog, GL_LINK_STATUS, &linked);
		
		if (linked != 1) {
			DebugNS::rDebug(1) << "program linking failed (id = " << prog << ") " << std::endl;

			int len = 0;

			glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);

			if (len > 0) {
				int charsWritten;
				char* log = new char[len];
				glGetProgramInfoLog(prog, len, &charsWritten, log);
				DebugNS::rDebug(1) << "Program Info Log: " << log << std::endl;
				delete[] log;
			}
		}
	}

	inline bool checkOpenGLError()
	{
		bool foundError = false;
		int glErr = glGetError();

		while (glErr != GL_NO_ERROR) {
			DebugNS::rDebug(1) << "glError: " << glErr << std::endl;
			foundError = true;
			glErr = glGetError();
		}
		return foundError;
	}
}

#else

namespace GLDebug {

	inline void printShaderLog(GLuint shader)
	{}

	inline void printProgramLog(GLuint prog)
	{}

	inline bool checkOpenGLError()
	{
		return false;
	}
}
#endif // DEBUG_BUILD