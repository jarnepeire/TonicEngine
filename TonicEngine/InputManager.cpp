#include "TonicEnginePCH.h"
#include "InputManager.h"
#include "Command.h"
#include <SDL.h>

bool Tonic::InputManager::ProcessInput()
{
	//Update state for next time
	m_PrevControllerState = m_CurrControllerState;

	//Getting SDL events
	SDL_Event e{};
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT)
		return false;

	//Reading the state of a controller: https://docs.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_state
	ZeroMemory(&m_CurrControllerState, sizeof(XINPUT_STATE));
	DWORD isControllerActive = XInputGetState(0, &m_CurrControllerState);

	//Describing the state through bitmask of the digital buttons: https://docs.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_gamepad
	//We're only looping over registered input buttons that actually have a command (action) bind to them
	for (std::pair<const InputSetting, std::shared_ptr<Command>>& it : m_InputActions)
	{
		auto& input = it.first;
		auto& command = it.second;

		//Execute command pressed by keyboard
		if (IsInputTriggered(input.KeyboardKey, input.TriggerState, e))
			command->Execute();

		if (isControllerActive == ERROR_SUCCESS)
		{
			//Execute command pressed by controller
			if (IsInputTriggered(input.Button, input.Type, input.TriggerState))
				command->Execute();
		}
	}

	//Updating mouse position
	m_PrevMousePos = m_CurrMousePos;
	m_PrevMouseButtonState = m_MouseButtonState;

	int mouseX{}, mouseY{};
	m_MouseButtonState = SDL_GetMouseState(&mouseX, &mouseY);
	m_CurrMousePos.x = (float)mouseX;
	m_CurrMousePos.y = (float)mouseY;

	m_RelativeMouseMove.x = m_CurrMousePos.x - m_PrevMousePos.x;
	m_RelativeMouseMove.y = m_CurrMousePos.y - m_PrevMousePos.y;

	//If all went well -> return true
	return true;
}

bool Tonic::InputManager::IsInputTriggered(ControllerButton button, ControllerButtonType type, TriggerState triggerState) const
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

bool Tonic::InputManager::IsInputTriggered(int keyboardKey, TriggerState triggerState) const
{
	//Getting SDL events
	SDL_Event e{};
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT)
		return false;

	//Execute command pressed by keyboard
	bool isHeld = (e.key.repeat != 0);
	if (!isHeld && e.type == SDL_KEYDOWN && triggerState == TriggerState::Pressed)
	{
		if ((int)e.key.keysym.scancode == keyboardKey)
			return true;
	}
	else if (!isHeld && e.type == SDL_KEYUP && triggerState == TriggerState::Released)
	{
		if ((int)e.key.keysym.scancode == keyboardKey)
			return true;
	}
	else if ((int)e.key.keysym.scancode == keyboardKey && isHeld && triggerState == TriggerState::Hold)
	{
		return true;
	}
	return false;
}

bool Tonic::InputManager::IsInputTriggered(int keyboardKey, TriggerState triggerState, SDL_Event& e) const
{
	//Execute command pressed by keyboard
	bool isHeld = (e.key.repeat != 0);
	if (!isHeld && e.type == SDL_KEYDOWN && triggerState == TriggerState::Pressed)
	{
		if ((int)e.key.keysym.scancode == keyboardKey)
			return true;
	}
	else if (!isHeld && e.type == SDL_KEYUP && triggerState == TriggerState::Released)
	{
		if ((int)e.key.keysym.scancode == keyboardKey)
			return true;
	}
	else if ((int)e.key.keysym.scancode == keyboardKey && isHeld && triggerState == TriggerState::Hold)
	{
		return true;
	}
	return false;
}

bool Tonic::InputManager::IsPressed(ControllerButton button) const
{
	return ((int)m_CurrControllerState.Gamepad.wButtons == (int)button);
}

bool Tonic::InputManager::WasPressed(ControllerButton button) const
{
	return ((int)m_PrevControllerState.Gamepad.wButtons == (int)button);
}

Tonic::TriggerState Tonic::InputManager::GetCurrentTriggerState(ControllerButton button) const
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

bool Tonic::InputManager::DidThumbstickMove(ControllerButton b) const
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

bool Tonic::InputManager::IsTriggerPressed(ControllerButton b) const
{
	if (b == ControllerButton::LeftTrigger)
		return m_CurrControllerState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
	else
		return (float)m_CurrControllerState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
}

void Tonic::InputManager::AddInputAction(int keyboardKey, ControllerButton button, ControllerButtonType type, TriggerState triggerState, std::shared_ptr<Command> command)
{
	InputSetting setting{};
	setting.Button = button;
	setting.KeyboardKey = keyboardKey;
	setting.Type = type;
	setting.TriggerState = triggerState;

	m_InputActions.insert(std::pair<InputSetting, std::shared_ptr<Command>>(setting, command));
}

bool Tonic::InputManager::IsMouseButtonDown(MouseButton btn, TriggerState triggerState) const
{
	if (triggerState == TriggerState::Hold)
	{
		return (m_MouseButtonState == Uint32(btn) && m_PrevMouseButtonState == Uint32(btn));
	}
	else if (triggerState == TriggerState::Pressed)
	{
		return (m_MouseButtonState == Uint32(btn) && m_PrevMouseButtonState != Uint32(btn));
	}
	else if (triggerState == TriggerState::Released)
	{
		return (m_MouseButtonState != Uint32(btn) && m_PrevMouseButtonState == Uint32(btn));
	}
	return false;
}

const glm::vec2& Tonic::InputManager::GetMousePos(bool getOldPos) const
{
	return (getOldPos) ? m_PrevMousePos : m_CurrMousePos;
}

glm::vec2 Tonic::InputManager::GetThumbstickDirectionNormalized(ControllerButton b) const
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

float Tonic::InputManager::GetTriggerForce(ControllerButton b) const
{
	if (b == ControllerButton::LeftTrigger)
		return (float)m_CurrControllerState.Gamepad.bLeftTrigger / 255.f;
	else
		return (float)m_CurrControllerState.Gamepad.bRightTrigger / 255.f;
}

void Tonic::InputManager::CarryOverInput(const InputManager& pInput)
{
	m_PrevMouseButtonState = pInput.m_PrevMouseButtonState;
	m_MouseButtonState = pInput.m_MouseButtonState;

	m_CurrMousePos = pInput.m_CurrMousePos;
	m_PrevMousePos = pInput.m_PrevMousePos;
	m_RelativeMouseMove = pInput.m_RelativeMouseMove;

	m_PrevControllerState = pInput.m_PrevControllerState;
	m_CurrControllerState = pInput.m_CurrControllerState;
}

