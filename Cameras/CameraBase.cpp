#include "CameraBase.h"
#include "../Render/Renderer.h"
#include "../Game.h"

void CameraBase::SetViewMatrix(const mat4& mat)
{
	GetGame()->GetRenderer()->SetViewMatrix(mat);
}