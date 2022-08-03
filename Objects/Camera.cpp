#include "Camera.h"
#include <SDL2/SDL_scancode.h>
#include "../Game.h"
#include "../Render/Renderer.h"
#include "../DebugLib/DebugOut.h"

void Camera::UpdateActor(float deltaTime)
{
	GameActor::UpdateActor(deltaTime);

	vec3 cameraPos = GetPosition();
	vec3 target = GetPosition() + vec3(0, 0, 100);

	mat4 view = mat4::CreateLookAt(cameraPos, target, vec3::UnitY);
	GetGame()->GetRenderer()->SetViewMatrix(view);
}

void Camera::ProcessInput(const uint8_t* keyState)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;

	if (keyState[SDL_SCANCODE_W])
	{
		forwardSpeed += 300.0f;
		Debug::Out(rSPAM) << "Moved forward" << std::endl;
	}
	if (keyState[SDL_SCANCODE_S])
	{
		forwardSpeed -= 300.0f;
		Debug::Out(rSPAM) << "Moved back" << std::endl;
	}
	if (keyState[SDL_SCANCODE_A])
	{
		angularSpeed -= Math::PI * 2;
		Debug::Out(rSPAM) << "Moved Left" << std::endl;
	}
	if (keyState[SDL_SCANCODE_D])
	{
		angularSpeed += Math::PI * 2;
		Debug::Out(rSPAM) << "Moved Right" << std::endl;
	}

	moveElem->SetForwardSpeed(forwardSpeed);
	moveElem->SetAngularSpeed(angularSpeed);
}