#include "TonicEnginePCH.h"
#include "HealthComponent.h"
#include "TextComponent.h"
#include "Subject.h"
#include "Observer.h"
#include "InputManager.h"
#include "RespawnComponent.h"
#include "GameEvent.h"

using namespace Tonic;
HealthComponent::HealthComponent(Tonic::GameObject* parent, int nbLives)
	: Component(parent)
	, m_NbLives(nbLives)
	, m_NbLivesOriginal(nbLives)
	, m_RespawnComponent()
	, m_HasDied()
{
}

void HealthComponent::Initialize()
{
}

void HealthComponent::PostInitialize()
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

void HealthComponent::SetNbLives(int lives)
{
	m_NbLives = lives;
	m_pSubject->Notify(m_pGameObject, (int)GameEvent::EVENT_CHARACTER_LOST_LIFE);
}

void HealthComponent::ResetLives()
{
	m_NbLives = m_NbLivesOriginal;
	m_pSubject->Notify(m_pGameObject, (int)GameEvent::EVENT_LEVEL_RESET);
}

void HealthComponent::LoseLife()
{
	--m_NbLives;
	if (m_NbLives > 0)
	{
		if (m_RespawnComponent)
			m_RespawnComponent->Respawn();
		m_pSubject->Notify(m_pGameObject, (int)GameEvent::EVENT_CHARACTER_LOST_LIFE);
	}
	else
	{
		//Notify death
		m_HasDied = true;
		m_pSubject->Notify(m_pGameObject, (int)GameEvent::EVENT_CHARACTER_DIED);
	}

}

void HealthComponent::SetRespawnComponent(std::shared_ptr<RespawnComponent> respawnComponent)
{
	m_RespawnComponent = respawnComponent;
}
