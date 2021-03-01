#include "TonicEnginePCH.h"
#include "Command.h"
#include "GameObject.h"
#include "CharacterComponent.h"
#include "HealthComponent.h"

void DieCommand::Execute()
{
	auto pHealth = m_pObject->GetComponent<HealthComponent>();
	if (pHealth)
	{
		pHealth->LoseLife();
	}
}

void ScoreCommand::Execute()
{
	auto pCharacter = m_pObject->GetComponent<CharacterComponent>();
	if (pCharacter)
	{
		//Score will vary based on what you did later
		pCharacter->GainScore(25);
	}
}
