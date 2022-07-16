#pragma once
#include "../Objects/Element.h"
//#include "Mesh.h"

class Shader;
class Mesh;

class MeshElement : public Element {
public:

	MeshElement(GameActor* owner_);

	void SetMesh(Mesh* mesh);

	void Draw(Shader* shader);

	ElementID GetType() const { return ElementID::MeshElement; }

	void SetVisible(bool visible_) { visible = false; }

private:
	Mesh* mesh;
	bool visible;
};