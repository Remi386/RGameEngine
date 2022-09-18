#include "InputSystem.h"
#include <SDL2/SDL_events.h>

void InputSystem::PreUpdate()
{
	std::memcpy(&inputState.keyboardState.previousState, 
				inputState.keyboardState.currentState,
			    sizeof(inputState.keyboardState.previousState));

	inputState.mouseState.previousMouseButtonsState = 
		inputState.mouseState.currentMouseButtonsState;

	inputState.mouseState.scrollWheelState = vec2();
}

void InputSystem::Update()
{
	int x, y;

	if (inputState.mouseState.isRelative)
		inputState.mouseState.currentMouseButtonsState = SDL_GetRelativeMouseState(&x, &y);
	else
		inputState.mouseState.currentMouseButtonsState = SDL_GetMouseState(&x, &y);

	inputState.mouseState.mousePosition = vec2(float(x), float(y));

}

void InputSystem::ProcessEvent(SDL_Event sdlEvent)
{
	switch (sdlEvent.type)
	{
	case SDL_MOUSEWHEEL:
		inputState.mouseState.mousePosition = 
			vec2(float(sdlEvent.wheel.x), float(sdlEvent.wheel.y));
		break;
	default:
		break;
	}
}

void InputSystem::SetRelativeMod(bool relative)
{ 
	inputState.mouseState.isRelative = relative;
	SDL_SetRelativeMouseMode((SDL_bool)relative);
}