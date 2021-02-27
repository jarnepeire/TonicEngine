#include "TonicEnginePCH.h"
#include "CharacterComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "InputManager.h"

using namespace dae;
CharacterComponent::CharacterComponent(dae::GameObject* parent)
	: Component(parent)
{
	m_pGameObject->GetSubject()->AddObserver(new CharacterObserver());
}

void CharacterComponent::FixedUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void CharacterComponent::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	//..stuff happens..
	//..suddenly we get blasted by a grenade and lose a life.. (replaced by the Input of a button for now)
	if (InputManager::GetInstance().IsInputTriggered(ControllerButton::ButtonA, ControllerButtonType::wButton, ControllerTriggerState::Pressed))
	{
		m_pGameObject->NotifySubject(Event::EVENT_ACTOR_LOST_LIFE);
	}
	//..continue code without having to fix anything for the health component, the Observer will take care of that..
}

void CharacterComponent::Render()
{
}