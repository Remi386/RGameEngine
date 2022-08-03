#include "Mesh.h"
#include "../DebugLib/DebugOut.h"
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>
#include "../Math/MathFunc.h"

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
	
	try {

		nlohmann::json json;

		file >> json;

		float version = json.at("version").get<float>();

		if (!Math::IsFEqual(version, 1.0f))
		{
			Debug::Out(rCRITICAL) << "Incompatible versions: game version =" << 1.0
				<< ", mesh version = " << version << std::endl;
			return false;
		}

		std::string vertexName = json.at("meshType").get<std::string>();

		VertexArray::VertexType vertType = VertexArray::GetVertexTypeByName(vertexName);

		std::vector<float> vertices = json.at("vertices").get<std::vector<float>>();
	
		std::vector<uint32_t> indices = json.at("indices").get<std::vector<uint32_t>>();

		verts = new VertexArray(vertices.data(), uint32_t(vertices.size()),
								indices.data(),  uint32_t(indices.size()),
								vertType);

	}
	catch (std::exception& e) {
		Debug::Out(rCRITICAL) << "Error in json reader: " << e.what() << std::endl;
		return false;
	}

	return true;
}