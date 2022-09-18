#include "Camera.h"
#include <SDL2/SDL_scancode.h>
#include "../Game.h"
#include "../Render/Renderer.h"
#include "../DebugLib/DebugOut.h"
#include "../Input/InputState.h"

void Camera::UpdateActor(float deltaTime)
{
	GameActor::UpdateActor(deltaTime);

	vec3 cameraPos = GetPosition();
	vec3 target = GetPosition() + GetForward() * 100;

	mat4 view = mat4::CreateLookAt(cameraPos, target, vec3::UnitY);
	GetGame()->GetRenderer()->SetViewMatrix(view);
}

void Camera::ProcessActorInput(const InputState& inputState)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;

	if (inputState.keyboardState.GetKeyPressed(SDL_SCANCODE_W))
	{
		forwardSpeed += 15.0f;
		Debug::Out(rSPAM) << "Moved forward" << std::endl;
	}
	if (inputState.keyboardState.GetKeyPressed(SDL_SCANCODE_S))
	{
		forwardSpeed -= 15.0f;
		Debug::Out(rSPAM) << "Moved back" << std::endl;
	}
	if (inputState.keyboardState.GetKeyPressed(SDL_SCANCODE_A))
	{
		angularSpeed -= Math::PI / 3;
		Debug::Out(rSPAM) << "Moved Left" << std::endl;
	}
	if (inputState.keyboardState.GetKeyPressed(SDL_SCANCODE_D))
	{
		angularSpeed += Math::PI / 3;
		Debug::Out(rSPAM) << "Moved Right" << std::endl;
	}

	moveElem->SetForwardSpeed(forwardSpeed);
	moveElem->SetAngularSpeed(angularSpeed);
}