#include "NextLevelObserver.h"
#include "HexGrid.h"
#include "SceneManager.h"
#include "QBertScene.h"
#include <GameObject.h>
#include "HealthComponent.h"
#include <CharacterComponent.h>

NextLevelObserver::NextLevelObserver(std::shared_ptr<HexGrid> currentLevelGrid, const std::string& nextLevelName)
	: m_pGrid(currentLevelGrid)
	, m_NextLevelName(nextLevelName)
{
}

void NextLevelObserver::Notify(dae::GameObject* object, Event e)
{
	if (e == Event::EVENT_PLAYER_LANDED)
	{
		if (m_pGrid->IsGridCompleted())
		{
			auto pScene = dae::SceneManager::GetInstance().GetScene(m_NextLevelName);
			auto qBertScene = dynamic_cast<QBertScene*>(pScene);
			if (qBertScene)
			{
				//First we clear scene
				qBertScene->ResetLevel();

				//Then update it with the current level information
				auto pHealth = object->GetComponent<HealthComponent>();
				if (pHealth)
					qBertScene->SetStartLives(pHealth->GetNbLives());

				auto pScore = object->GetComponent<CharacterComponent>();
				if (pScore)
					qBertScene->SetStartScore(pScore->GetScore());
			}
			dae::SceneManager::GetInstance().SetActiveScene(m_NextLevelName);
		}
	}
}
