#pragma once
#include <cstdint>
#include <string>

class VertexArray {
public:
	enum class VertexType : int {
		Vert, //Array contains only vertices, 3 floats
		Vert_Text, //Array contains vertices and texels, 5 floats
		Vert_Norm_Text //Array contains vertices, normals and texels, 8 floats
				
	};

	VertexArray(const void* vertData, uint32_t vertSize,
				const uint32_t* indicesData, uint32_t indicesSize, VertexType vertType);

	~VertexArray();

	void SetActive();

	uint32_t GetVertsSize() const { return VertexBufferSize; }

	uint32_t GetIndicesSize() const { return IndexBufferSize; }

	uint32_t GetVertexSizeByType(VertexType type);

	static VertexType GetVertexTypeByName(const std::string& VertexName);

private:

	void SpecifyAttributes(VertexType type, uint32_t vertSize);

	uint32_t VertexBufferSize = 0;
	uint32_t IndexBufferSize = 0;

	uint32_t VertexArrayID = 0;
	uint32_t VertexBufferID = 0;
	uint32_t IndexBufferID = 0;
};
