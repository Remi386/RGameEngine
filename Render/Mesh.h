#pragma once
#include <string>

class VertexArray;
class Texture;

class Mesh {
public:

	Mesh(class Renderer* renderer);

	VertexArray* const GetVertexArray() const { return verts; }

	Texture* GetTexture() { return texture; }

	~Mesh();

protected:

	bool LoadMesh(const std::string& fileName);

private:

	class Renderer* renderer = nullptr;
	VertexArray* verts = nullptr;
	Texture* texture = nullptr;

	friend Renderer;
};