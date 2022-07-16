#pragma once

class GameActor;

class Element {
public:

	/*class ElementComparator {
	public:
		bool operator()(Element* lhs, Element* rhs) {
			return lhs->GetPriority() < rhs->GetPriority();
		}
	};*/

	enum class ElementID : int {
		MeshElement
	};

	Element(GameActor* owner_)
		: owner(owner_)
	{}

	//int GetPriority() { return priority; }

	virtual ElementID GetType() const = 0;

protected:
	GameActor* owner;
	//int priority;
};