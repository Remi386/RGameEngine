#include "Shader.h"
#include <fstream>
#include "../DebugLib/DebugOut.h"
#include "../DebugLib/GL_Debug.h"
#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "../Math/mat4.h"

bool Shader::Load(const std::string& vertShader, const std::string& fragShader)
{
	if (!LoadShader(vertShader, GL_VERTEX_SHADER, vertexShaderID) ||
		!LoadShader(fragShader, GL_FRAGMENT_SHADER, fragmentShaderID)) 
	{
		Unload();
		return false;
	}

	shaderProgramID = glCreateProgram();
	GLDebug::CheckOpenGLError();

	glAttachShader(shaderProgramID, vertexShaderID);
	GLDebug::CheckOpenGLError();

	glAttachShader(shaderProgramID, fragmentShaderID);
	GLDebug::CheckOpenGLError();

	glLinkProgram(shaderProgramID);
	GLDebug::CheckOpenGLError();

	if (!ProgramLinked())
	{
		Unload();
		return false;
	}

	return true;
}

void Shader::SetActive()
{
	glUseProgram(shaderProgramID);
}

void Shader::Unload()
{
	constexpr uint32_t MaxUintValue = std::numeric_limits<uint32_t>::max();

	if (shaderProgramID != MaxUintValue)
		glDeleteProgram(vertexShaderID);

	if (vertexShaderID != MaxUintValue)
		glDeleteShader(vertexShaderID);

	if (fragmentShaderID != MaxUintValue)
		glDeleteShader(vertexShaderID);
}

bool Shader::LoadShader(const std::string& shaderName, uint32_t shaderType, uint32_t& outID)
{
	std::ifstream file(shaderName.c_str(), std::ios::ate);

	if (!file.is_open()) {
		Debug::Out(rIMPORTANT) << "Can not open shader file: " << shaderName << std::endl;
		return false;
	}

	size_t length = file.tellg();
	file.seekg(0, std::ios::beg);

	std::string content;
	content.reserve(length);
	file.read(content.data(), length);
	const char* contentPointer = content.c_str();

	outID = glCreateShader(shaderType);
	GLDebug::CheckOpenGLError();

	glShaderSource(outID, 1, &contentPointer, nullptr);
	GLDebug::CheckOpenGLError();

	glCompileShader(outID);
	GLDebug::CheckOpenGLError();

	if (!ShaderCompiled(outID))
	{
		Debug::Out(rIMPORTANT) << "compilation of shader "
			<< shaderName << " failed" << std::endl;
		return false;
	}

	return true;
}

void Shader::SetUniformMatrix4(std::string_view matName, const mat4& mat)
{
	GLuint loc = GetUniformLocation(matName);
	
	glUniformMatrix4fv(loc, 1, GL_FALSE, mat.GetPointer());
}

void Shader::SetUniformVector3(std::string_view vecName, const vec3& vec)
{
	GLuint loc = GetUniformLocation(vecName);

	glUniform3fv(loc, 1, vec.GetPointer());
}

void Shader::SetUniformFloat(std::string_view floatName, float value)
{
	GLuint loc = GetUniformLocation(floatName);

	glUniform1f(loc, value);
}

GLuint Shader::GetUniformLocation(std::string_view uniName)
{
	GLuint loc = glGetUniformLocation(shaderProgramID, uniName.data());

	GLDebug::CheckOpenGLError();
	Debug::Assert(loc != uintMax, rIMPORTANT,
				  "Cant get uniform variable location: " + std::string(uniName));

	return loc;
}

#ifdef DEBUG_BUILD

bool Shader::ShaderCompiled(uint32_t ShaderID)
{
	GLint vertCompiled;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &vertCompiled);

	if (vertCompiled != 1) {
		Debug::Out(rCRITICAL) << "shader compilation failed (id = " 
							  << ShaderID << ") " << std::endl;

		int len = 0;

		glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &len);

		if (len > 0) {
			int charsWritten;
			char* log = new char[len];

			glGetShaderInfoLog(ShaderID, len, &charsWritten, log);
			Debug::Out(rCRITICAL) << "Shader Info Log: " << log << std::endl;

			delete[] log;
		}
		return false;
	}

	return true;
}

bool Shader::ProgramLinked()
{
	GLint linked;

	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &linked);

	if (linked != 1) {
		Debug::Out(rCRITICAL) << "program linking failed (id = "
							  << shaderProgramID << ") " << std::endl;

		int len = 0;

		glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &len);

		if (len > 0) {
			int charsWritten;
			char* log = new char[len];
			glGetProgramInfoLog(shaderProgramID, len, &charsWritten, log);
			Debug::Out(rCRITICAL) << "Program Info Log: " << log << std::endl;
			delete[] log;
		}

		return false;
	}

	return  true;
}

#else

bool Shader::ShaderCompiled(uint32_t ShaderID)
{
	return true;
}

bool Shader::ProgramLinked()
{
	return true;
}

#endif // DEBUG_SYMB