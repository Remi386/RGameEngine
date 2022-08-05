#include "Texture.h"
#include <SOIL2/SOIL2.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include "../DebugLib/DebugOut.h"

bool Texture::Load(std::string_view fileName)
{
	int channels = 0;
	unsigned char* image = SOIL_load_image(fileName.data(), &width, 
										   &height, &channels, SOIL_LOAD_AUTO);

	if (image == nullptr) {
		Debug::Out(rCRITICAL) <<  "Failed to load texture: " << fileName << std::endl;
		return false;
	}

	int ColorFormat = (channels == 4) ? GL_RGBA : GL_RGB;
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, ColorFormat, width, height, 0, ColorFormat,
				 GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Enable anisotropic filtering
	if (GLEW_EXT_texture_filter_anisotropic)
	{
		GLfloat largest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
	}

	return true;
}

void Texture::SetActive()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}