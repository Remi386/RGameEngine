#pragma once
#include "../Objects/Element.h"

class Shader;
class Mesh;

class MeshElement : public Element {
public:

	MeshElement(GameActor* owner_);

	void SetMesh(Mesh* mesh);

	void Draw(Shader* shader);

	ElementType GetType() const { return ElementType::MeshElement; }

	void SetVisible(bool visible_) { visible = false; }

private:
	Mesh* mesh;
	bool visible;
};