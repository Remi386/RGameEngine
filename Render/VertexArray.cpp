#include "VertexArray.h"
#include <GL/glew.h>
#include "../DebugLib/DebugOut.h"
#include "../DebugLib/GL_Debug.h"
#include "../Objects/ObjectID.h"

VertexArray::VertexArray(const void* vertData, uint32_t vertCount,
	const uint32_t* indicesData, uint32_t indicesCount, VertexType vertType)
{
	VertexBufferSize = vertCount;
	IndexBufferSize = indicesCount;

	//Vertex array
	glGenVertexArrays(1, &VertexArrayID);
	GLDebug::CheckOpenGLError();

	glBindVertexArray(VertexArrayID);
	GLDebug::CheckOpenGLError();

	uint32_t vertSize = GetVertexSizeByType(vertType);

	//Vertex buffer
	glGenBuffers(1, &VertexBufferID);
	GLDebug::CheckOpenGLError();
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	GLDebug::CheckOpenGLError();
	glBufferData(GL_ARRAY_BUFFER, vertCount * vertSize, vertData, GL_STATIC_DRAW);
	GLDebug::CheckOpenGLError();

	//Index buffer
	glGenBuffers(1, &IndexBufferID);
	GLDebug::CheckOpenGLError();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);
	GLDebug::CheckOpenGLError();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(uint32_t), indicesData, GL_STATIC_DRAW);
	GLDebug::CheckOpenGLError();

	SpecifyAttributes(vertType, vertSize);
}

void VertexArray::SetActive()
{
	glBindVertexArray(VertexArrayID);
}

//Freeing up resources from GPU memory
VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &IndexBufferID);
	glDeleteBuffers(1, &VertexBufferID);
	glDeleteVertexArrays(1, &VertexArrayID);
}

//Return vertex size in bytes
uint32_t VertexArray::GetVertexSizeByType(VertexType type)
{
	switch (type)
	{
	case VertexArray::VertexType::Vert:
		return sizeof(float) * 3;
	case VertexArray::VertexType::Vert_Text:
		return sizeof(float) * 5;
	case VertexArray::VertexType::Vert_Norm_Text:
		return sizeof(float) * 8;
	default:
		Debug::Out(rCRITICAL) << "Got unknown type in VertexArray size, id = " << int(type) << std::endl;
		std::terminate();
	}
}

void VertexArray::SpecifyAttributes(VertexType type, uint32_t vertSize)
{
	switch (type)
	{
	case VertexArray::VertexType::Vert:
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertSize, 0);
		GLDebug::CheckOpenGLError();
		glEnableVertexAttribArray(0);
		GLDebug::CheckOpenGLError();
		break;
	case VertexArray::VertexType::Vert_Text:
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertSize, 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertSize, 
			reinterpret_cast<void*>(sizeof(float) * 3));
		break;
	case VertexArray::VertexType::Vert_Norm_Text:
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertSize, 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertSize,
			reinterpret_cast<void*>(sizeof(float) * 3));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertSize,
			reinterpret_cast<void*>(sizeof(float) * 6));
		break;
	default:
		Debug::Out(rCRITICAL) << "Got unknown type in VertexArray attr, id = " << int(type) << std::endl;
		std::terminate();
	}
}

VertexArray::VertexType VertexArray::GetVertexTypeByName(const std::string& VertName)
{
	switch (fnHash(VertName))
	{
	case "Vert"_sID:
		return VertexType::Vert;
	case "Vert_Text"_sID:
		return VertexType::Vert_Text;
	case "Vert_Norm_Text"_sID:
		return VertexType::Vert_Norm_Text;
	default:
		Debug::Out(rIMPORTANT) << "Unknown vertex type: " << VertName << std::endl;
		return VertexType::Vert;
	}
}

VertexArray* VertexArray::CreateSpriteVertexArray()
{
	float verts[] = {
		-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f 
	};

	unsigned int inds[] = {
		0, 1, 2,
		2, 3, 0
	};

	return new VertexArray(verts, sizeof(verts) / sizeof(float), 
						   inds, sizeof(inds) / sizeof(uint32_t), 
						   VertexType::Vert_Text);
}