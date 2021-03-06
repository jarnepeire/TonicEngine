#pragma once
#include "InputManager.h"

namespace Tonic
{
	class InputLocator final
	{
	public:
		static InputManager& GetInputManager() { return *m_pInputManager; }
		static void RegisterInputManager(InputManager* pInputManager);

	private:
		InputLocator();

		static InputManager m_pNullInput;
		static InputManager* m_pInputManager;
	};
}

