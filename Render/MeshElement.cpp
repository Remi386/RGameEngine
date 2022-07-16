#include "MeshElement.h"
#include "Mesh.h"
#include "Shader.h"
#include "GL/glew.h"
#include "../Game.h"
#include "../Objects/GameActor.h"
#include "Renderer.h"

MeshElement::MeshElement(GameActor* owner_)
	:Element(owner_)
{
	owner->GetGame()->GetRenderer()->AddMeshElement(this);
}

void MeshElement::SetMesh(Mesh* mesh_)
{
	mesh = mesh_;
}

void MeshElement::Draw(Shader* shader)
{
	VertexArray* const v = mesh->GetVertexArray();

	glDrawElements(GL_TRIANGLES, v->GetIndicesSize(), GL_UNSIGNED_INT, nullptr);
}