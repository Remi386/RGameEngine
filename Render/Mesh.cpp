#include "Mesh.h"
#include "../DebugLib/DebugOut.h"
#include <fstream>
#include <sstream>

Mesh::Mesh(class Renderer* renderer_)
{
	renderer = renderer_;
}

Mesh::~Mesh()
{
	delete verts;
}

bool Mesh::LoadMesh(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open()) {
		Debug::Out(rCRITICAL) << "Cannot open mesh file: " << fileName << std::endl;
		return false;
	}

	std::string line;

	std::getline(file, line);
	VertexArray::VertexType vertType = VertexArray::GetVertexTypeByName(line);

	std::vector<float> vertices;
	std::vector<uint32_t> indices;

	while (!file.eof()) {

		char controlChar;
		std::getline(file, line);
		std::stringstream sStream(line);

		if (line.empty())
			continue;

		sStream >> controlChar;

		if (controlChar == '/' || controlChar == ' ')
			continue;

		if (controlChar == 'v') { //vertex
			float v[3];
			sStream >> v[0] >> v[1] >> v[2];
			vertices.push_back(v[0]);
			vertices.push_back(v[1]);
			vertices.push_back(v[2]);
		}
		if (controlChar == 'f') //surface
		{
			uint32_t ind[3];
			sStream >> ind[0] >> ind[1] >> ind[2];
			indices.push_back(ind[0]);
			indices.push_back(ind[1]);
			indices.push_back(ind[2]);
		}

	}

	verts = new VertexArray(vertices.data(), vertices.size(),
		indices.data(), indices.size(),
		vertType);

	return true;
}