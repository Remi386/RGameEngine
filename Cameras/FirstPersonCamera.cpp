#include "FirstPersonCamera.h"
#include "../Input/InputState.h"

void FirstPersonCamera::ProcessActorInput(const InputState& state)
{
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;
	float angularSpeed = 0.0f;
	float pitchSpeed = 0.0f;

	if (state.keyboardState.GetKeyPressed(SDL_SCANCODE_W)) {
		forwardSpeed += 20.0f;
	}

	if (state.keyboardState.GetKeyPressed(SDL_SCANCODE_S)) {
		forwardSpeed -= 20.0f;
	}

	if (state.keyboardState.GetKeyPressed(SDL_SCANCODE_A)) {
		strafeSpeed -= 20.0f;
	}

	if (state.keyboardState.GetKeyPressed(SDL_SCANCODE_D)) {
		strafeSpeed += 20.0f;
	}

	vec2 mouse = state.mouseState.GetPosition();

	if (mouse.x != 0) {
		angularSpeed = float(mouse.x) / MaxAngularSpeed;
		angularSpeed *= MaxMouseSpeed;
	}

	if (mouse.y != 0) {
		pitchSpeed = float(mouse.y) / MaxPitchSpeed;
		pitchSpeed *= MaxMouseSpeed;
	}

	moveElem.SetForwardSpeed(forwardSpeed);
	moveElem.SetStrafeSpeed(strafeSpeed);
	moveElem.SetAngularSpeed(angularSpeed);

	setPitchSpeed(pitchSpeed);
}

void FirstPersonCamera::UpdateActor(float deltaTime)
{
	currentPitch += pitchSpeed * deltaTime;
	currentPitch = Math::Clamp(-MaxPitch, MaxPitch, currentPitch);

	quat pitchRot = quat(GetRight(), currentPitch);

	vec3 camPos = GetPosition();
	vec3 forward = vec3::Transform(GetForward(), pitchRot);

	vec3 target = camPos + forward * 100.0f;

	vec3 up = vec3::Transform(vec3::UnitY, pitchRot);

	mat4 viewMat = mat4::CreateLookAt(camPos, target, up);
	SetViewMatrix(viewMat);
}