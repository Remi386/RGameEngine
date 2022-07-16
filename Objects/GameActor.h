#pragma once
#include <vector>
#include <queue>
//#include "Element.h"
class Element;
class Game;

class GameActor {
public:

	GameActor(Game* game_);

	Game* GetGame() { return game; }

	virtual void Update() {};

	void AddElement(Element* elem) { elements.push_back(elem); }

private:
	std::vector<Element*> elements;
	Game* game;
};