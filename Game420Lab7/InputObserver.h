#pragma once
#include "Box2D\Common\b2Math.h"
#include <SDL.h>
#include <SDL_keyboard.h>

//holds the mouse update data
struct KeyboardEventArgs
{
	SDL_keysym KeyboardSym;
	Uint8 KeyboardState;

	KeyboardEventArgs()
	{
		KeyboardSym;
		KeyboardState = 0;
	}
	KeyboardEventArgs(SDL_keysym _KeyboardSym, Uint8 _KeyboardState)
	{
		KeyboardSym = _KeyboardSym;
		KeyboardState = _KeyboardState;
	}

};
struct MouseButtonEventArgs
{
	Uint8 ButtonIndex;
	Uint8 ButtonState;
	b2Vec2 MousePosition;
	MouseButtonEventArgs()
	{
		ButtonIndex = 0;
		ButtonState = 0;
		MousePosition = b2Vec2_zero;
	}
	MouseButtonEventArgs(Uint8 _ButtonIndex, Uint8 _ButtonState, b2Vec2 _MousePosition)
	{
		ButtonIndex = _ButtonIndex;
		ButtonState = _ButtonState;
		MousePosition = _MousePosition;

	}
};
struct MouseMovementEventArgs
{
	b2Vec2 MouseMovement;
	b2Vec2 RelativeMouseMovement;
	MouseMovementEventArgs()
	{
		MouseMovement = b2Vec2_zero;
		RelativeMouseMovement = b2Vec2_zero;
	}
	MouseMovementEventArgs(b2Vec2 _MouseMovement, b2Vec2 _RelativeMouseMovement)
	{
		MouseMovement = _MouseMovement;
		RelativeMouseMovement = _RelativeMouseMovement;
	}
};

class InputObserver
{
public:
	InputObserver(void);
	virtual void OnKeyEvent(KeyboardEventArgs) = 0;
	virtual void OnMouseButton(MouseButtonEventArgs) = 0;
	virtual void OnMouseMove(MouseMovementEventArgs) = 0;
	virtual ~InputObserver(void);
};
