#include "GameActor.h"
#include "Element.h"
#include "../DebugLib/DebugOut.h"
#include "../Game.h"
#include "../Input/InputState.h"

GameActor::GameActor(Game* game_)
	:game(game_)
{
	game->AddGameActor(this);
}

GameActor::~GameActor()
{
	game->RemoveGameActor(this);
}

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

void GameActor::ProcessInput(const InputState& inputState)
{
	for (auto elem : elements) {
		elem->ProcessInput(inputState);
	}

	ProcessActorInput(inputState);
}

void GameActor::UpdateWorldTransform(float deltaTime)
{
	if (updateWorldTransform) {

    	mat4 wrldTrans = mat4::CreateFromQuaternion(rotation);
		wrldTrans *= mat4::CreateScale(scale);
		wrldTrans *= mat4::CreateTranslation(position);
		worldTransform = wrldTrans;
		updateWorldTransform = false;
	}
}

Element* GameActor::GetElementByType(Element::ElementType elemType)
{
	auto iter = std::find_if(elements.begin(), elements.end(),
					[elemType](Element* elem) {
						return elem->GetType() == elemType;
					});

	return iter == elements.end() ? nullptr : *iter;
}