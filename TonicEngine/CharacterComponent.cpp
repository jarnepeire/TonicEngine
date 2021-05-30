#include "TonicEnginePCH.h"
#include "CharacterComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "InputManager.h"
#include "Subject.h"

using namespace dae;
CharacterComponent::CharacterComponent(dae::GameObject* parent)
	: Component(parent)
	, m_Score(0)
{
}

void CharacterComponent::FixedUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void CharacterComponent::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void CharacterComponent::Render()
{
}

void CharacterComponent::GainScore(int score)
{
	m_Score += score;
	m_pSubject->Notify(m_pGameObject, Event::EVENT_PLAYER_SCORED);
}

void CharacterComponent::ResetScore()
{
	m_Score = 0;
	m_pSubject->Notify(m_pGameObject, Event::EVENT_LEVEL_RESET);
}
