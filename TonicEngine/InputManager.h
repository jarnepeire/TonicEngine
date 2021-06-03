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
#include <SDL_events.h>

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

	struct InputSettingALT
	{
		//Simple constructor
		InputSettingALT() {}
		InputSettingALT(ControllerButton button, ControllerButtonType type, TriggerState triggerState)
		{
			Button = button;
			Type = type;
			TriggerState = triggerState;
		}

		// operator== is required to compare keys in case of hash collision
		bool operator==(const InputSettingALT& is) const
		{
			return (Button == is.Button
				&& KeyboardKey == is.KeyboardKey
				&& Type == is.Type
				&& TriggerState == is.TriggerState
				/*&& Command == is.Command*/);
		}

		// operator< is required to compare keys in case of hash collision
		// ordered on keyboard key
		bool operator<(const InputSettingALT& is) const
		{
			return KeyboardKey < is.KeyboardKey;
		}

		//Member variables
		ControllerButton Button{};
		int KeyboardKey{};
		ControllerButtonType Type{};
		TriggerState TriggerState{};
		//std::shared_ptr<Command> Command{ nullptr };
	};

	class InputManager final
	{
	public:
		InputManager() = default;

		bool ProcessInput();
		bool IsInputTriggered(ControllerButton button, ControllerButtonType type, TriggerState triggerState);
		bool IsInputTriggered(int keyboardKey, TriggerState triggerState);
		void AddInputAction(int keyboardKey, ControllerButton button, ControllerButtonType type, TriggerState triggerState, std::shared_ptr<Command> command);

		bool IsMouseButtonDown(MouseButton btn, TriggerState triggerState) const;
		const glm::vec2& GetRelativeMouseMove() const { return m_RelativeMouseMove; }
		const glm::vec2& GetMousePos(bool getOldPos = false) const;
		glm::vec2 GetThumbstickDirectionNormalized(ControllerButton button);
		float GetTriggerForce(ControllerButton button);

	private:
		Uint32 m_PrevMouseButtonState;
		Uint32 m_MouseButtonState;
		glm::vec2 m_CurrMousePos, m_PrevMousePos, m_RelativeMouseMove;

		XINPUT_STATE m_PrevControllerState;
		XINPUT_STATE m_CurrControllerState;
		//std::map<dae::InputSetting, std::shared_ptr<Command>> m_InputActions;
		std::map<dae::InputSettingALT, std::shared_ptr<Command>> m_InputActions;

		/* Private functions */
		bool IsInputTriggered(int keyboardKey, TriggerState triggerState, SDL_Event& e);
		bool IsPressed(ControllerButton button) const;
		bool WasPressed(ControllerButton button) const;

		dae::TriggerState GetCurrentTriggerState(ControllerButton button);
		bool DidThumbstickMove(ControllerButton button);
		bool IsTriggerPressed(ControllerButton button);

	};

}
