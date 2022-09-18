#pragma once
#include <vector>
#include "../Math/quaternion.h"
#include "../Math/vec3.h"
#include "../Math/mat4.h"
#include "Element.h"
#include "../utils/PriorityVector.h"

class Game;
struct InputState;

class GameActor {
public:

	GameActor(Game* game_);
	
	~GameActor();

	Game* GetGame() { return game; }

	const mat4& WorldTransform() { return worldTransform; }

	void SetPosition(const vec3& pos) { position = pos; updateWorldTransform = true; }

	void SetRotation(const quat& rot) { rotation = rot; updateWorldTransform = true; }

	void SetScale(float scale_) { scale = scale_; updateWorldTransform = true; }

	void Update(float deltaTime);
	
	virtual void UpdateActor(float deltaTime) {};

	void ProcessInput(const InputState& inputState);
	
	virtual void ProcessActorInput(const InputState& inputState) {}

	void AddElement(Element* elem);

	void RemoveElement(Element* elem);

	Element* GetElementByType(Element::ElementType elemType);

	quat GetRotation() const { return rotation; }

	vec3 GetPosition() const { return position; }

	vec3 GetForward() const { return vec3::Transform(vec3::UnitZ, rotation); }

	vec3 GetRight() const { return vec3::Transform(vec3::UnitX, rotation); }

	vec3 GetUp() const { return vec3::Transform(vec3::UnitY, rotation); }

private:

	void UpdateElements(float deltaTime);

	void UpdateWorldTransform(float);

	PriorityVector<Element*, ElementLessComparator> elements;
	Game* game;

	quat rotation;
	vec3 position;
	float scale = 1.0f;
	
	mat4 worldTransform;
	bool updateWorldTransform = true;
};