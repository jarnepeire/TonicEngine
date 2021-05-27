//#pragma once
//#include <Windows.h>
//#include <Xinput.h>
//#include <map>
//#include <unordered_map>
//#include <vector>
//#include <memory>
//
//#include "Command.h"
//#include "Singleton.h"
//#include "KeyboardMapping.h"
//#include "ControllerMapping.h"
//
//#pragma warning (disable:4201)
//#include "glm/glm.hpp"
//
//namespace dae
//{
//	enum class TriggerState
//	{
//		NULL_VALUE = -666,
//		Pressed,
//		Released,
//		Hold
//	};
//
//	struct InputSetting
//	{
//		//Simple constructor
//		InputSetting() {}
//		InputSetting(ControllerButton button, ControllerButtonType type, TriggerState triggerState)
//		{
//			Button = button;
//			Type = type;
//			TriggerState = triggerState;
//		}
//
//		// operator== is required to compare keys in case of hash collision
//		bool operator==(const InputSetting& is) const
//		{
//			return Button == is.Button && TriggerState == is.TriggerState;
//		}
//
//		// operator< is required to compare keys in case of hash collision
//		bool operator<(const InputSetting& is) const
//		{
//			return Button < is.Button;
//		}
//
//		//Member variables
//		ControllerButton Button{};
//		int KeyboardKey{};
//		ControllerButtonType Type{};
//		TriggerState TriggerState{};
//		mutable bool IsTriggered = false;
//	};
//
//	class InputManager final : public Singleton<InputManager>
//	{
//	public:
//		InputManager() = default;
//
//		bool ProcessInput();
//		bool IsInputTriggered(ControllerButton button, ControllerButtonType type, TriggerState triggerState);
//		void AddInputAction(int keyboardKey, ControllerButton button, ControllerButtonType type, TriggerState triggerState, std::shared_ptr<Command> command);
//
//		glm::vec2 GetThumbstickDirectionNormalized(ControllerButton button);
//		float GetTriggerForce(ControllerButton button);
//
//	private:
//		XINPUT_STATE m_PrevControllerState;
//		XINPUT_STATE m_CurrControllerState;
//		std::map<dae::InputSetting, std::shared_ptr<Command>> m_InputActions;
//		//std::unordered_map<dae::InputSetting, std::shared_ptr<Command>> m_InputActions;
//
//		/* Private functions */
//		bool IsPressed(ControllerButton button) const;
//		bool WasPressed(ControllerButton button) const;
//
//		dae::TriggerState GetCurrentTriggerState(ControllerButton button);
//		bool DidThumbstickMove(ControllerButton button);
//		bool IsTriggerPressed(ControllerButton button);
//	};
//
//}

#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <map>
#include <unordered_map>
#include <vector>
#include <memory>

#include "Command.h"
#include "Singleton.h"
#include "KeyboardMapping.h"
#include "ControllerMapping.h"

#pragma warning (disable:4201)
#include "glm/glm.hpp"

namespace dae
{
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

	class InputManager final
	{
	public:
		InputManager() = default;

		bool ProcessInput();
		bool IsInputTriggered(ControllerButton button, ControllerButtonType type, TriggerState triggerState);
		void AddInputAction(int keyboardKey, ControllerButton button, ControllerButtonType type, TriggerState triggerState, std::shared_ptr<Command> command);

		glm::vec2 GetThumbstickDirectionNormalized(ControllerButton button);
		float GetTriggerForce(ControllerButton button);

	private:
		XINPUT_STATE m_PrevControllerState;
		XINPUT_STATE m_CurrControllerState;
		std::map<dae::InputSetting, std::shared_ptr<Command>> m_InputActions;
		//std::unordered_map<dae::InputSetting, std::shared_ptr<Command>> m_InputActions;

		/* Private functions */
		bool IsPressed(ControllerButton button) const;
		bool WasPressed(ControllerButton button) const;

		dae::TriggerState GetCurrentTriggerState(ControllerButton button);
		bool DidThumbstickMove(ControllerButton button);
		bool IsTriggerPressed(ControllerButton button);
	};

}
