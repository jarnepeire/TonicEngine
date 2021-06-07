#include "TonicEnginePCH.h"
#include "CharacterComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "InputManager.h"
#include "Subject.h"
#include "GameEvent.h"

using namespace Tonic;
CharacterComponent::CharacterComponent()
	: Component()
	, m_Score(0)
{
}

void CharacterComponent::Initialize()
{
}

void CharacterComponent::PostInitialize()
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
	m_pSubject->Notify(m_pGameObject, (int)GameEvent::EVENT_PLAYER_SCORED);
}

void CharacterComponent::ResetScore()
{
	m_Score = 0;
	m_pSubject->Notify(m_pGameObject, (int)GameEvent::EVENT_LEVEL_RESET);
}
