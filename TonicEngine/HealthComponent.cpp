#include "TonicEnginePCH.h"
#include "HealthComponent.h"
#include "TextComponent.h"
#include "Subject.h"
#include "Observer.h"
#include "InputManager.h"

using namespace dae;
HealthComponent::HealthComponent(dae::GameObject* parent, int nbLives)
	: Component(parent)
	, m_NbLives(nbLives)
{
}

void HealthComponent::FixedUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void HealthComponent::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void HealthComponent::Render()
{
}

void HealthComponent::LoseLife()
{
	--m_NbLives;
	m_pSubject->Notify(m_pGameObject, Event::EVENT_PLAYER_LOST_LIFE);
}
