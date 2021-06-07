#pragma once
#include <SDL_mouse.h>

namespace Tonic
{
	enum class ControllerButton
	{
		NULL_VALUE = -666,

		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,

		ButtonDPAD_Up = XINPUT_GAMEPAD_DPAD_UP,
		ButtonDPAD_Down = XINPUT_GAMEPAD_DPAD_DOWN,
		ButtonDPAD_Left = XINPUT_GAMEPAD_DPAD_LEFT,
		ButtonDPAD_Right = XINPUT_GAMEPAD_DPAD_RIGHT,

		ButtonStart = XINPUT_GAMEPAD_START,
		ButtonBack = XINPUT_GAMEPAD_BACK,

		ButtonLeftThumbstick = XINPUT_GAMEPAD_LEFT_THUMB,
		ButtonRightThumbstick = XINPUT_GAMEPAD_RIGHT_THUMB,

		ButtonLS = XINPUT_GAMEPAD_LEFT_SHOULDER,
		ButtonRS = XINPUT_GAMEPAD_RIGHT_SHOULDER,

		//Reason for this, is to keep the simplicity of having 1 enum class to define all possible input buttons
		//Since there's only 2 triggers, and 2 thumbsticks, they get differentated by ControllerButtonType
		LeftTrigger = -1,
		RightTrigger = -2,

		LeftThumbstick = -3,
		RightThumbstick = -4
	};

	enum class ControllerButtonType
	{
		NULL_VALUE = -666,
		wButton,
		Trigger,
		Thumbstick
	};

	enum class MouseButton
	{
		NULL_VALUE = 0,
		LMB = SDL_BUTTON(1),
		RMB = SDL_BUTTON(3),
		LRMB = (SDL_BUTTON(1) + SDL_BUTTON(3))
	};
}