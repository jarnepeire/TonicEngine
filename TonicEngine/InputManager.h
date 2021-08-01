#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <map>
#include <memory>
#include "KeyboardMapping.h"
#include "ControllerMapping.h"

#pragma warning (disable:4201)
#include "glm/glm.hpp"
#include <SDL_events.h>

namespace Tonic
{
	class Command;

	enum class TriggerState
	{
		NULL_VALUE = -666,
		Pressed,
		Released,
		Hold
	};

	struct InputSetting
	{
		//Simple constructor
		InputSetting() {}
		InputSetting(Tonic::ControllerButton button, Tonic::ControllerButtonType type, Tonic::TriggerState triggerState)
		{
			Button = button;
			Type = type;
			TriggerState = triggerState;
		}

		// operator== is required to compare keys in case of hash collision
		bool operator==(const InputSetting& is) const
		{
			return (Button == is.Button
				&& KeyboardKey == is.KeyboardKey
				&& Type == is.Type
				&& TriggerState == is.TriggerState);
		}

		// operator< is required to compare keys in case of hash collision
		// ordered on keyboard key
		bool operator<(const InputSetting& is) const
		{
			return KeyboardKey < is.KeyboardKey;
		}

		//Member variables
		Tonic::ControllerButton Button{};
		int KeyboardKey{};
		Tonic::ControllerButtonType Type{};
		Tonic::TriggerState TriggerState{};
	};

	class InputManager final
	{
	public:
		InputManager() = default;

		/* Process all types of input and returns whether the window is being terminated or not */
		bool ProcessInput();
		
		/* Returns true if combination of controller button and type is triggered in the given state */
		bool IsInputTriggered(Tonic::ControllerButton button, Tonic::ControllerButtonType type, Tonic::TriggerState triggerState) const;
		
		/* Returns true if combination of keyboard key in the given state is triggered */
		bool IsInputTriggered(int keyboardKey, Tonic::TriggerState triggerState) const;
		
		/* Adds a new command to the manager to be executed on certain key inputs */
		void AddInputAction(int keyboardKey, Tonic::ControllerButton button, Tonic::ControllerButtonType type, Tonic::TriggerState triggerState, std::shared_ptr<Tonic::Command> command);

		/* Returns true if given mouse button is triggered in the given trigger state */
		bool IsMouseButtonDown(Tonic::MouseButton btn, Tonic::TriggerState triggerState) const;
		
		/* Returns relative movement vector of the mouse since previous frame */
		const glm::vec2& GetRelativeMouseMove() const { return m_RelativeMouseMove; }
		
		/* Returns mouse position */
		const glm::vec2& GetMousePos(bool getOldPos = false) const;
		
		/* Returns vector of direction in which thumbstick is being rotated */
		glm::vec2 GetThumbstickDirectionNormalized(Tonic::ControllerButton button) const;
		
		/* Returns trigger force of the controller trigger given */
		float GetTriggerForce(Tonic::ControllerButton button) const;

		/* Makes sure the old input before this went inactive doesn't impact the game when this scene becomes active again */
		void CarryOverInput(const InputManager& pInput);

	private:
		Uint32 m_PrevMouseButtonState{};
		Uint32 m_MouseButtonState{};
		glm::vec2 m_CurrMousePos{}, m_PrevMousePos{}, m_RelativeMouseMove{};

		XINPUT_STATE m_PrevControllerState{};
		XINPUT_STATE m_CurrControllerState{};
		std::map<Tonic::InputSetting, std::shared_ptr<Tonic::Command>> m_InputActions{};

		/* Private functions */
		bool IsInputTriggered(int keyboardKey, Tonic::TriggerState triggerState, SDL_Event& e) const;
		bool IsPressed(Tonic::ControllerButton button) const;
		bool WasPressed(Tonic::ControllerButton button) const;

		Tonic::TriggerState GetCurrentTriggerState(Tonic::ControllerButton button) const;
		bool DidThumbstickMove(Tonic::ControllerButton button) const;
		bool IsTriggerPressed(Tonic::ControllerButton button) const;
	};

}
