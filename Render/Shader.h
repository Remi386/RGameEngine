#pragma once
#include <string>
#include <limits>

class Shader {
public:

	bool Load(const std::string& vertShader, const std::string& fragShader);

	void Unload();

	void SetActive();

private:

	bool LoadShader(const std::string& ShaderName, uint32_t shaderType, uint32_t& outID);

	bool ShaderCompiled(uint32_t ShaderID);

	bool ProgramLinked();

	uint32_t vertexShaderID = std::numeric_limits<uint32_t>::max();
	uint32_t fragmentShaderID = std::numeric_limits<uint32_t>::max();
	uint32_t shaderProgramID = std::numeric_limits<uint32_t>::max();

};