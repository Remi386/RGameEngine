#pragma once
#include <string>
#include <limits>
#include <string_view>
#include "../Math/Math.h"

constexpr uint32_t uintMax = std::numeric_limits<uint32_t>::max();

class Shader {
public:

	bool Load(const std::string& vertShader, const std::string& fragShader);

	void Unload();

	void SetUniformMatrix4(std::string_view matName, const mat4& mat);

	void SetUniformVector3(std::string_view vecName, const vec3& vec);

	void SetUniformFloat(std::string_view floatName, float value);

	void SetActive();

private:
	bool LoadShader(const std::string& ShaderName, uint32_t shaderType, uint32_t& outID);

	uint32_t GetUniformLocation(std::string_view uniName);

	bool ShaderCompiled(uint32_t ShaderID);

	bool ProgramLinked();

	uint32_t vertexShaderID = uintMax;
	uint32_t fragmentShaderID = uintMax;
	uint32_t shaderProgramID = uintMax;
};