#include "TonicEnginePCH.h"
#include "InputManager.h"
#include <SDL.h>

bool dae::InputManager::ProcessInput()
{
	//Update state for next time
	m_PreviousState = m_CurrentState;

	//Reading the state of a controller: https://docs.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_state
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	if (XInputGetState(0, &m_CurrentState) == ERROR_SUCCESS)
	{
		//Describing the state through bitmask of the digital buttons: https://docs.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_gamepad
		//We're only looping over registered input buttons that actually have a command (action) bind to them
		for (std::pair<const InputSetting, std::shared_ptr<Command>>& it : m_InputActions)
		{
			//Execute command that is bound to input
			if (IsInputTriggered(it.first.Button, it.first.Type, it.first.TriggerState))
				it.second->Execute();
		}
	}

	//Mouse Events
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	//If all went well -> return true
	return true;
}

bool dae::InputManager::IsInputTriggered(ControllerButton button, ControllerButtonType type, ControllerTriggerState triggerState)
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
	return ((int)m_CurrentState.Gamepad.wButtons == (int)button);
}

bool dae::InputManager::WasPressed(ControllerButton button) const
{
	return ((int)m_PreviousState.Gamepad.wButtons == (int)button);
}

dae::ControllerTriggerState dae::InputManager::GetCurrentTriggerState(ControllerButton button)
{
	//Full credit to: https://bell0bytes.eu/xinput-and-gamepads/
	//For the way of detecting whether a button was hold/released/pressed
	if (WasPressed(button))
		if (IsPressed(button))
			return ControllerTriggerState::Hold;
		else
			return ControllerTriggerState::Released;
	else
		if (IsPressed(button))
			return ControllerTriggerState::Pressed;
		else
			return ControllerTriggerState::NULL_VALUE;
}

bool dae::InputManager::DidThumbstickMove(ControllerButton b)
{
	if (b == ControllerButton::LeftThumbstick)
	{
		//Get left thumb information
		float LX = m_CurrentState.Gamepad.sThumbLX;
		float LY = m_CurrentState.Gamepad.sThumbLY;

		//Determine how far the controller is pushed
		float magnitudeLeftSqrd = LX * LX + LY * LY;

		//Check if the controller is outside a circular dead zone
		return (magnitudeLeftSqrd > (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));
	}
	else
	{
		//Get right thumb information
		float RX = m_CurrentState.Gamepad.sThumbRX;
		float RY = m_CurrentState.Gamepad.sThumbRY;

		//Determine how far the controller is pushed
		float magnitudeRightSqrd = RX * RX + RY * RY;

		//Check if the controller is outside a circular dead zone
		return (magnitudeRightSqrd > (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE * XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
	}
}

bool dae::InputManager::IsTriggerPressed(ControllerButton b)
{
	if (b == ControllerButton::LeftTrigger)
		return m_CurrentState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
	else
		return (float)m_CurrentState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
}

void dae::InputManager::AddInputAction(ControllerButton button, ControllerButtonType type, ControllerTriggerState triggerState, std::shared_ptr<Command> command)
{
	InputSetting setting{};
	setting.Button = button;
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
		x = m_CurrentState.Gamepad.sThumbLX;
		y = m_CurrentState.Gamepad.sThumbLY;
		deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	}
	else
	{
		x = m_CurrentState.Gamepad.sThumbRX;
		y = m_CurrentState.Gamepad.sThumbRY;
		deadzone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	}

	//Determine how far the controller is pushed
	float magnitudeSqrd = x * x + y * y;

	//Normalized values
	float xNormalized = (x < 0.f) ? -(x * x) / magnitudeSqrd : (x * x) / magnitudeSqrd;
	float yNormalized = (y < 0.f) ? -(y * y) / magnitudeSqrd : (y * y) / magnitudeSqrd;
	xNormalized++;
	yNormalized++;
	return glm::vec2(xNormalized, yNormalized);
}

float dae::InputManager::GetTriggerForce(ControllerButton b)
{
	if (b == ControllerButton::LeftTrigger)
		return (float)m_CurrentState.Gamepad.bLeftTrigger / 255.f;
	else
		return (float)m_CurrentState.Gamepad.bRightTrigger / 255.f;
}

