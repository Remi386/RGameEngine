#pragma once

#include "InputState.h"

union SDL_Event;
class Game;

class InputSystem {
public:

	friend Game;

	void PreUpdate();
	
	void Update();

	InputState& GetInputState() { return inputState; }

	void ProcessEvent(SDL_Event sdlEvent);

private:
	InputState inputState;
};