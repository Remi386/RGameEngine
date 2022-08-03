#pragma once
#include "GameActor.h"
#include "MoveElement.h"

class Camera : public GameActor {
public:
	Camera(Game* game)
		:GameActor(game), moveElem(new MoveElement(this, 40))
	{}

	virtual void UpdateActor(float deltaTime) override;

	void ProcessInput(const uint8_t* keyState) override;

private:
	MoveElement* moveElem;
};