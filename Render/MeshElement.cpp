#include "MeshElement.h"
#include "Mesh.h"
#include "Shader.h"
#include "GL/glew.h"
#include "../Game.h"
#include "../Objects/GameActor.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Texture.h"

MeshElement::MeshElement(GameActor* owner_)
	:Element(owner_), visible(false), mesh(nullptr)
{
	owner->GetGame()->GetRenderer()->AddMeshElement(this);
}

void MeshElement::SetMesh(Mesh* mesh_)
{
	mesh = mesh_;
}

void MeshElement::Draw(Shader* shader)
{
	shader->SetUniformMatrix4("worldTransform", owner->WorldTransform());

	VertexArray* const v = mesh->GetVertexArray();
	v->SetActive();

	mesh->GetTexture()->SetActive();

	glDrawElements(GL_TRIANGLES, v->GetIndicesSize(), GL_UNSIGNED_INT, nullptr);
}