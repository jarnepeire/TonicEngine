#include "EndGameObserver.h"
#include <GameObject.h>
#include "SceneManager.h"
#include "GameOverMenu.h"
#include "CharacterComponent.h"
#include "AudioLocator.h"
#include "GameEvent.h"

using namespace Tonic;
EndGameObserver::EndGameObserver(const std::string& endGameSceneName, unsigned int endGameSoundId)
	:  m_EndGameSceneName(endGameSceneName)
	, m_EndGameSoundID(endGameSoundId)
{
}

void EndGameObserver::Notify(Tonic::GameObject* object, int eventId)
{
	if (eventId == (int)GameEvent::EVENT_CHARACTER_DIED)
	{
		auto pScene = Tonic::SceneManager::GetInstance().GetScene(m_EndGameSceneName);
		auto pGameOverScene = dynamic_cast<GameOverMenu*>(pScene);
		if (pGameOverScene)
		{
			auto pScoreComp = object->GetComponent<CharacterComponent>();
			if (pScoreComp)
				pGameOverScene->SetFinalScore(pScoreComp->GetScore());
		}

		AudioLocator::GetAudioSystem().Play(m_EndGameSoundID, 0.25f);
		Tonic::SceneManager::GetInstance().SetActiveScene(m_EndGameSceneName);
	}
}
