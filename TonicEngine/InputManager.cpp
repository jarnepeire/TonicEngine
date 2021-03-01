#include "TonicEnginePCH.h"
#include "InputManager.h"
#include <SDL.h>

bool dae::InputManager::ProcessInput()
{
	//Update state for next time
	m_PrevControllerState = m_CurrControllerState;

	//Getting SDL events
	SDL_Event e;
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT) 
		return false;

	//Reading the state of a controller: https://docs.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_state
	ZeroMemory(&m_CurrControllerState, sizeof(XINPUT_STATE));
	if (XInputGetState(0, &m_CurrControllerState) == ERROR_SUCCESS)
	{
		//Describing the state through bitmask of the digital buttons: https://docs.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_gamepad
		//We're only looping over registered input buttons that actually have a command (action) bind to them
		for (std::pair<const InputSetting, std::shared_ptr<Command>>& it : m_InputActions)
		{
			auto& input = it.first;
			auto& command = it.second;

			//Execute command pressed by keyboard
			bool isHeld = (e.key.repeat != 0);
			if (!isHeld && e.type == SDL_KEYDOWN && input.TriggerState == TriggerState::Pressed)
			{
				if ((int)e.key.keysym.scancode == input.KeyboardKey)
					command->Execute();
			}
			else if (!isHeld && e.type == SDL_KEYUP && input.TriggerState == TriggerState::Released)
			{
				if ((int)e.key.keysym.scancode == input.KeyboardKey)
					command->Execute();
			}
			else if ((int)e.key.keysym.scancode == input.KeyboardKey && isHeld && input.TriggerState == TriggerState::Hold)
			{
				command->Execute();
			}

			//Execute command pressed by controller
			if (IsInputTriggered(input.Button, input.Type, input.TriggerState))
				command->Execute();
		}
	}

	//If all went well -> return true
	return true;
}

bool dae::InputManager::IsInputTriggered(ControllerButton button, ControllerButtonType type, TriggerState triggerState)
{
	//Check if the input that is requested matches the current state of input
	switch (type)
	{
	case ControllerButtonType::wButton:
		return (GetCurrentTriggerState(button) == triggerState);
		break;

	case ControllerButtonType::Trigger:
		return (IsTriggerPressed(button));
		break;

	case ControllerButtonType::Thumbstick:
		return (DidThumbstickMove(button));
		break;

	default:
		return false;
		break;
	}
	
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	return ((int)m_CurrControllerState.Gamepad.wButtons == (int)button);
}

bool dae::InputManager::WasPressed(ControllerButton button) const
{
	return ((int)m_PrevControllerState.Gamepad.wButtons == (int)button);
}

dae::TriggerState dae::InputManager::GetCurrentTriggerState(ControllerButton button)
{
	//Full credit to: https://bell0bytes.eu/xinput-and-gamepads/
	//For the way of detecting whether a button was hold/released/pressed
	if (WasPressed(button))
		if (IsPressed(button))
			return TriggerState::Hold;
		else
			return TriggerState::Released;
	else
		if (IsPressed(button))
			return TriggerState::Pressed;
		else
			return TriggerState::NULL_VALUE;
}

bool dae::InputManager::DidThumbstickMove(ControllerButton b)
{
	if (b == ControllerButton::LeftThumbstick)
	{
		//Get left thumb information
		float LX = m_CurrControllerState.Gamepad.sThumbLX;
		float LY = m_CurrControllerState.Gamepad.sThumbLY;

		//Determine how far the controller is pushed
		float magnitudeLeftSqrd = LX * LX + LY * LY;

		//Check if the controller is outside a circular dead zone
		return (magnitudeLeftSqrd > (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));
	}
	else
	{
		//Get right thumb information
		float RX = m_CurrControllerState.Gamepad.sThumbRX;
		float RY = m_CurrControllerState.Gamepad.sThumbRY;

		//Determine how far the controller is pushed
		float magnitudeRightSqrd = RX * RX + RY * RY;

		//Check if the controller is outside a circular dead zone
		return (magnitudeRightSqrd > (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE * XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
	}
}

bool dae::InputManager::IsTriggerPressed(ControllerButton b)
{
	if (b == ControllerButton::LeftTrigger)
		return m_CurrControllerState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
	else
		return (float)m_CurrControllerState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
}

void dae::InputManager::AddInputAction(int keyboardKey, ControllerButton button, ControllerButtonType type, TriggerState triggerState, std::shared_ptr<Command> command)
{
	InputSetting setting{};
	setting.Button = button;
	setting.KeyboardKey = keyboardKey;
	setting.Type = type;
	setting.TriggerState = triggerState;

	m_InputActions.insert(std::pair<InputSetting, std::shared_ptr<Command>>(setting, command));
}

glm::vec2 dae::InputManager::GetThumbstickDirectionNormalized(ControllerButton b)
{
	//Source: https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput
	//Determine which thumbstick to calculate direction for
	float x{}, y{};
	int deadzone{};
	if (b == ControllerButton::LeftThumbstick)
	{
		x = m_CurrControllerState.Gamepad.sThumbLX;
		y = m_CurrControllerState.Gamepad.sThumbLY;
		deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	}
	else
	{
		x = m_CurrControllerState.Gamepad.sThumbRX;
		y = m_CurrControllerState.Gamepad.sThumbRY;
		deadzone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	}

	//Determine how far the controller is pushed
	float magnitudeSqrd = x * x + y * y;

	//Normalized values
	float xNormalized = (x < 0.f) ? -(x * x) / magnitudeSqrd : (x * x) / magnitudeSqrd;
	float yNormalized = (y < 0.f) ? -(y * y) / magnitudeSqrd : (y * y) / magnitudeSqrd;

	return glm::vec2(xNormalized, yNormalized);
}

float dae::InputManager::GetTriggerForce(ControllerButton b)
{
	if (b == ControllerButton::LeftTrigger)
		return (float)m_CurrControllerState.Gamepad.bLeftTrigger / 255.f;
	else
		return (float)m_CurrControllerState.Gamepad.bRightTrigger / 255.f;
}

