#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <map>
#include <vector>
#include <memory>

#include "Command.h"
#include "Singleton.h"

#pragma warning (disable:4201)
#include "glm/glm.hpp"

namespace dae
{
	
	enum class ControllerButton
	{
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
		wButton,
		Trigger,
		Thumbstick
	};

	enum class TriggerState
	{
		NULL_VALUE,
		Pressed,
		Released,
		Hold
	};

	struct InputSetting
	{
		//Simple constructor
		InputSetting() {}
		InputSetting(ControllerButton button, ControllerButtonType type, TriggerState triggerState)
		{
			Button = button;
			Type = type;
			TriggerState = triggerState;
		}

		// operator== is required to compare keys in case of hash collision
		bool operator==(const InputSetting& is) const
		{
			return Button == is.Button && TriggerState == is.TriggerState;
		}

		// operator< is required to compare keys in case of hash collision
		bool operator<(const InputSetting& is) const
		{
			return Button < is.Button;
		}

		//Member variables
		ControllerButton Button{};
		int KeyboardKey{};
		ControllerButtonType Type{};
		TriggerState TriggerState{};
		mutable bool IsTriggered = false;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:

		bool ProcessInput();
		bool IsInputTriggered(ControllerButton button, ControllerButtonType type, TriggerState triggerState);
		void AddInputAction(int keyboardKey, ControllerButton button, ControllerButtonType type, TriggerState triggerState, std::shared_ptr<Command> command);

		glm::vec2 GetThumbstickDirectionNormalized(ControllerButton button);
		float GetTriggerForce(ControllerButton button);

	private:
		XINPUT_STATE m_PrevControllerState;
		XINPUT_STATE m_CurrControllerState;
		std::map<dae::InputSetting, std::shared_ptr<Command>> m_InputActions;

		/* Private functions */
		bool IsPressed(ControllerButton button) const;
		bool WasPressed(ControllerButton button) const;

		dae::TriggerState GetCurrentTriggerState(ControllerButton button);
		bool DidThumbstickMove(ControllerButton button);
		bool IsTriggerPressed(ControllerButton button);
	};

}
