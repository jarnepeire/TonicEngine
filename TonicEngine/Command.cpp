#include "TonicEnginePCH.h"
#include "Command.h"
#include "GameObject.h"
#include "CharacterComponent.h"
#include "HealthComponent.h"

#include "ServiceLocator.h"

void DieCommand::Execute()
{
	auto pHealth = m_pObject->GetComponent<HealthComponent>();
	if (pHealth)
	{
		pHealth->LoseLife();
		ServiceLocator::GetAudioSystem().Play(Event::EVENT_PLAYER_LOST_LIFE, 0.25f);
	}
}

void ScoreCommand::Execute()
{
	auto pCharacter = m_pObject->GetComponent<CharacterComponent>();
	if (pCharacter)
	{
		//Score will vary based on what you did later
		pCharacter->GainScore(25);
		ServiceLocator::GetAudioSystem().Play(Event::EVENT_PLAYER_SCORED, 0.25f);
	}
}
