#pragma once
#include "VertexArray.h"
#include <string>

class Mesh {
public:

	Mesh(class Renderer* renderer);

	bool LoadMesh(const std::string& fileName);

	VertexArray* const GetVertexArray() const { return verts; }

	~Mesh();

private:

	class Renderer* renderer = nullptr;
	VertexArray* verts = nullptr;
};