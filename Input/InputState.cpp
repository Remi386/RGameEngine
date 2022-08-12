#include "InputState.h"
#include <SDL2/SDL_keyboard.h>

KeyboardState::KeyboardState()
{
	currentState = SDL_GetKeyboardState(nullptr);

	std::memset(&previousState, 0, sizeof(previousState));
}

bool KeyboardState::GetKeyPressed(SDL_Scancode scancode) const
{
	return currentState[scancode];
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode scancode) const
{
	return static_cast<ButtonState>(
		(previousState[scancode] << 1) | currentState[scancode]);
}

bool MouseState::GetButtonPressed(SDL_Scancode scancode) const
{
	return (SDL_BUTTON(scancode) & currentMouseButtonsState);
}

ButtonState MouseState::GetButtonState(SDL_Scancode scancode) const
{
	int mask = SDL_BUTTON(scancode);

	return static_cast<ButtonState>(
		((mask & previousMouseButtonsState) << 1) | (mask & currentMouseButtonsState));
}