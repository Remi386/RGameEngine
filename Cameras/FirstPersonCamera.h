#pragma once
#include "CameraBase.h"
#include "../Objects/MoveElement.h"

class FirstPersonCamera : public CameraBase {
public:

	FirstPersonCamera(Game* game)
		: CameraBase(game), moveElem(this)
	{}

	virtual void ProcessActorInput(const InputState& input) override;

	virtual void UpdateActor(float deltaTime) override;

	void setPitchSpeed(float speed) { pitchSpeed = speed; }

	void setPitch(float pitch) { currentPitch = pitch; }

	void setMaxPitchSpeed(float speed) { MaxPitchSpeed = speed; }

	void setMaxAngularSpeed(float speed) { MaxAngularSpeed = speed; }
	
	void setMaxMouseSpeed(float speed) { MaxMouseSpeed = speed; }

private:
	float pitchSpeed      = 0.0f;
	float currentPitch    = 0.0f;

	float MaxPitch        = Math::PI / 3;
	float MaxMouseSpeed   = Math::PI / 8;
	float MaxPitchSpeed   = Math::PI / 3;
	float MaxAngularSpeed = Math::PI / 3;

	MoveElement moveElem;
};