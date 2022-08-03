#pragma once
#include <string>
#include <limits>
#include <string_view>
#include "../Math/Math.h"

class Shader {
public:
	bool Load(const std::string& vertShader, const std::string& fragShader);

	void Unload();

	void SetUniformMatrix4(std::string_view matName, const mat4& mat);

	void SetUniformVector3(std::string_view matName, const vec3& mat);

	void SetUniformFloat(std::string_view matName, float mat);

	void SetActive();

private:
	bool LoadShader(const std::string& ShaderName, uint32_t shaderType, uint32_t& outID);

	bool ShaderCompiled(uint32_t ShaderID);

	bool ProgramLinked();

	uint32_t vertexShaderID = std::numeric_limits<uint32_t>::max();
	uint32_t fragmentShaderID = std::numeric_limits<uint32_t>::max();
	uint32_t shaderProgramID = std::numeric_limits<uint32_t>::max();
};