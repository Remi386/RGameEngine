#include "MoveElement.h"
#include "../Math/MathFunc.h"
#include "GameActor.h"

MoveElement::MoveElement(GameActor* owner, int priority /* = 50*/)
	:Element(owner, priority)
{}

void MoveElement::Update(float deltaTime)
{

	if (!Math::IsZero(forwardSpeed))
	{
		vec3 pos = owner->GetPosition();
		pos += owner->GetForward() * forwardSpeed * deltaTime;
		owner->SetPosition(pos);
	}

	if (!Math::IsZero(strafeSpeed))
	{
		vec3 pos = owner->GetPosition();
		pos += owner->GetRight() * strafeSpeed * deltaTime;
		owner->SetPosition(pos);
	}

	if (!Math::IsZero(angularSpeed)) {
		quat rot = owner->GetRotation();

		float angle = angularSpeed * deltaTime;
		quat inc(vec3::UnitY, angle);

		rot *= inc;
		owner->SetRotation(rot);
	}

	if (!Math::IsZero(pitchSpeed)) {
		quat rot = owner->GetRotation();

		float angle = pitchSpeed * deltaTime;
		quat inc(vec3::UnitX, angle);
		
		rot *= inc;
		owner->SetRotation(rot);
	}
}