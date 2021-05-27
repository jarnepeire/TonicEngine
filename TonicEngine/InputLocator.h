#pragma once
#include "InputManager.h"

namespace dae
{
	class InputLocator final
	{
	public:
		static InputManager& GetInputManager() { return *m_pInputManager; }
		static void RegisterInputManager(InputManager* pInputManager);

	private:
		InputLocator();

		//static std::mutex m_Mutex;
		static InputManager m_pNullInput;
		static InputManager* m_pInputManager;
	};
}

