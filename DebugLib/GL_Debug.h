#pragma once

#include <GL/glew.h>
#include "DebugOut.h"

#ifdef DEBUG_BUILD

namespace GLDebug {

	inline bool CheckOpenGLError()
	{
		bool foundError = false;
		int glErr = glGetError();

		while (glErr != GL_NO_ERROR) {
			Debug::Out(rIMPORTANT) << "glError: " << glErr << std::endl;
			foundError = true;
			glErr = glGetError();
		}
		return foundError;
	}

#else

	inline bool CheckOpenGLError()
	{
		return false;
	}
#endif // DEBUG_BUILD
}