#pragma once

#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_mouse.h>
#include "../Math/vec2.h"

class InputSystem;

// With c++17 we can write binary literals
// As we can see, previous state represents most significant bit
// So we can calculate button state by bitwise operations
enum class ButtonState : uint8_t {
	None     = 0b00, // previous state = 0, current state = 0
	Pressed  = 0b01, // previous state = 0, current state = 1
	Released = 0b10, // previous state = 1, current state = 0
	Held     = 0b11  // previous state = 1, current state = 1
};

class KeyboardState {
public:

	// Only InputSystem class can edit this state
	friend InputSystem;

	KeyboardState();

	/// <summary>
	/// Is key pressed right now
	/// </summary>
	/// <param name="scancode"></param>
	/// <returns></returns>
	bool GetKeyPressed(SDL_Scancode scancode) const;

	/// <summary>
	/// Get button state, which can be "None", "Pressed", "Held" and "Released"
	/// </summary>
	/// <param name="scancode"></param>
	/// <returns></returns>
	ButtonState GetKeyState(SDL_Scancode scancode) const;

private:
	//Note: key state automatically updates after all sdl events processed
	const uint8_t* currentState;

	uint8_t previousState[SDL_NUM_SCANCODES];
};

class MouseState {
public:

	// Only InputSystem class can edit this state
	friend InputSystem;

	vec2 GetPosition() const { return mousePosition; }

	vec2 GetScrollWheelState() const { return scrollWheelState; }

	/// <summary>
	/// Is button pressed right now
	/// </summary>
	/// <param name="scancode"></param>
	/// <returns></returns>
	bool GetButtonPressed(SDL_Scancode scancode) const;

	/// <summary>
	/// Get button state, which can be "None", "Pressed", "Held" and "Released"
	/// </summary>
	/// <param name="scancode"></param>
	/// <returns></returns>
	ButtonState GetButtonState(SDL_Scancode scancode) const;

	bool IsRelative() const { return isRelative; }

private:

	vec2 mousePosition;
	vec2 scrollWheelState;

	uint32_t currentMouseButtonsState = 0;
	uint32_t previousMouseButtonsState = 0;
	bool isRelative = false;

};

struct InputState
{
	KeyboardState keyboardState;
	MouseState mouseState;
};