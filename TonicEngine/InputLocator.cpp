#include "TonicEnginePCH.h"
#include "InputLocator.h"

dae::InputManager* dae::InputLocator::m_pInputManager = nullptr;
dae::InputManager dae::InputLocator::m_pNullInput = dae::InputManager();

dae::InputLocator::InputLocator()
{
	m_pInputManager = &m_pNullInput;
}

void dae::InputLocator::RegisterInputManager(InputManager* pInputManager)
{
	if (pInputManager)
		m_pInputManager = pInputManager;
	else
		m_pInputManager = &m_pNullInput;
}
