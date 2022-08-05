#pragma once

#include <string>
#include <string_view>

class Renderer;

class Texture {
public:

	void SetActive();

protected:

	bool Load(std::string_view fileName);

private:
	uint32_t textureID = std::numeric_limits<uint32_t>::max();
	int width = 0;
	int height = 0;

	friend Renderer;
};