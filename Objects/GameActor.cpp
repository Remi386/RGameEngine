#include "GameActor.h"
#include "Element.h"

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
	UpdateWorldTransform(deltaTime);
	UpdateActor(deltaTime);
}

void GameActor::UpdateWorldTransform(float deltaTime)
{
	//worldTransform *= mat4::CreateFromQuaternion(rotation);
	static float angle = 0;
	
	angle += deltaTime * 0.4;

	mat4 wrldTrans;
	wrldTrans *= mat4::CreateRotationX(Math::ToRadians(angle));
	wrldTrans *= mat4::CreateRotationY(Math::ToRadians(angle));
	wrldTrans *= mat4::CreateScale(scale);
	wrldTrans *= mat4::CreateTranslation(position);
	worldTransform = wrldTrans;
	updateWorldTransform = false;
}

