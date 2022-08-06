#include "GameActor.h"
#include "Element.h"
#include "../DebugLib/DebugOut.h"

GameActor::GameActor(Game* game_)
	:game(game_)
{}

void GameActor::AddElement(Element* elem)
{ 
	elements.AddValue(elem);
}

void GameActor::RemoveElement(Element* elem)
{
	elements.Erase(elem);
}

void GameActor::Update(float deltaTime)
{
	UpdateElements(deltaTime);
	UpdateActor(deltaTime);
	UpdateWorldTransform(deltaTime);
}

void GameActor::UpdateElements(float deltaTime)
{
	for (auto elem : elements) {
		elem->Update(deltaTime);
	}
}

void GameActor::UpdateWorldTransform(float deltaTime)
{
	if (updateWorldTransform) {
		mat4 wrldTrans;
		wrldTrans *= mat4::CreateFromQuaternion(rotation);
		wrldTrans *= mat4::CreateScale(scale);
		wrldTrans *= mat4::CreateTranslation(position);
		worldTransform = wrldTrans;

		Debug::Out(rSPAM) << "Position: " << position << std::endl;
		Debug::Out(rSPAM) << "Rotation: " << rotation << std::endl;
		Debug::Out(rSPAM) << "Look at position: " << GetForward() * 100 << std::endl;

		updateWorldTransform = false;
	}
}

