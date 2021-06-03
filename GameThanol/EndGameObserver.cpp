#include "EndGameObserver.h"
#include <GameObject.h>
#include "SceneManager.h"
#include "GameOverMenu.h"
#include "CharacterComponent.h"

EndGameObserver::EndGameObserver(const std::string& endGameSceneName)
	:  m_EndGameSceneName(endGameSceneName)
{
}

void EndGameObserver::Notify(dae::GameObject* object, Event e)
{
	if (e == Event::EVENT_PLAYER_DIED)
	{
		auto pScene = dae::SceneManager::GetInstance().GetScene(m_EndGameSceneName);
		auto pGameOverScene = dynamic_cast<GameOverMenu*>(pScene);
		if (pGameOverScene)
		{
			auto pScoreComp = object->GetComponent<CharacterComponent>();
			if (pScoreComp)
				pGameOverScene->SetFinalScore(pScoreComp->GetScore());
		}

		dae::SceneManager::GetInstance().SetActiveScene(m_EndGameSceneName);
	}
}
