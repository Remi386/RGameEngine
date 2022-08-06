#pragma once

class GameActor;

class Element {
public:

	enum class ElementID : int {
		MeshElement,
		MoveElement
	};

	Element(GameActor* owner_, int priority_ = 100);

	virtual void Update(float deltaTime) {}

	int GetPriority() const { return priority; }

	virtual ElementID GetType() const = 0;

protected:
	GameActor* owner;
	int priority;
};

class ElementLessComparator {
public:
	bool operator()(const Element* lhs, const Element* rhs) {
		return lhs->GetPriority() < rhs->GetPriority();
	}
};

class ElementGreaterComparator {
public:
	bool operator()(const Element* lhs, const Element* rhs) {
		return lhs->GetPriority() > rhs->GetPriority();
	}
};