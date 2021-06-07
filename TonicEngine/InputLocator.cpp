#include "TonicEnginePCH.h"
#include "InputLocator.h"

Tonic::InputManager* Tonic::InputLocator::m_pInputManager = nullptr;
Tonic::InputManager Tonic::InputLocator::m_pNullInput = Tonic::InputManager();

Tonic::InputLocator::InputLocator()
{
	m_pInputManager = &m_pNullInput;
}

void Tonic::InputLocator::RegisterInputManager(InputManager* pInputManager)
{
	if (pInputManager)
		m_pInputManager = pInputManager;
	else
		m_pInputManager = &m_pNullInput;
}
