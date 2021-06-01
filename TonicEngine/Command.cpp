#include "TonicEnginePCH.h"
#include "Command.h"
#include "GameObject.h"
#include "CharacterComponent.h"
#include "HealthComponent.h"
#include "AudioLocator.h"

void DieCommand::Execute()
{
	auto pHealth = m_pObject->GetComponent<HealthComponent>();
	if (pHealth)
	{
		pHealth->LoseLife();
		AudioLocator::GetAudioSystem().Play(m_SoundID, 0.2f);
	}
}

void ScoreCommand::Execute()
{

	auto pCharacter = m_pObject->GetComponent<CharacterComponent>();
	if (pCharacter)
	{
		//Score will vary based on what you did later
		pCharacter->GainScore(25);

		std::cout << "Requesting 4 times the Score sound, to display the fix for the same layered sound\n";
		AudioLocator::GetAudioSystem().Play(m_SoundID, 0.1f);
		AudioLocator::GetAudioSystem().Play(m_SoundID, 0.1f);
		AudioLocator::GetAudioSystem().Play(m_SoundID, 0.1f);
		AudioLocator::GetAudioSystem().Play(m_SoundID, 0.1f);
		
	}
}
