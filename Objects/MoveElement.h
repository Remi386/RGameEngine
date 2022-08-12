#pragma once
#include "Element.h"

class MoveElement : public Element {
public:
	MoveElement(GameActor* owner, int priority = 50);

	virtual void Update(float deltaTime) override;

	virtual ElementType GetType() const override { return ElementType::MoveElement; }

	void SetAngularSpeed(float speed) { angularSpeed = speed; };
	
	void SetForwardSpeed(float speed) { forwardSpeed = speed; };

private:
	float angularSpeed = 0.0f;
	float forwardSpeed = 0.0f;
};