#include "WinGameObserver.h"
#include <GameObject.h>
#include "SceneManager.h"
#include "HexGrid.h"
#include "WinningGameMenu.h"
#include "QBertScene.h"
#include "GameScores.h"
#include "CharacterComponent.h"
WinGameObserver::WinGameObserver(std::shared_ptr<HexGrid> currentLevelGrid, const std::string& winningSceneName)
	: m_pGrid(currentLevelGrid)
	, m_WinningSceneName(winningSceneName)
{
}

void WinGameObserver::Notify(dae::GameObject* object, Event e)
{
	if (e == Event::EVENT_JUMPER_LANDED)
	{
		if (m_pGrid->IsGridCompleted())
		{
			auto pScene = dae::SceneManager::GetInstance().GetScene(m_WinningSceneName);
			auto pWinningScene = dynamic_cast<WinningGameMenu*>(pScene);
			if (pWinningScene)
			{
				//Set final score
				auto pPrevScene = object->GetParentScene();
				auto pPrevQBertScene = dynamic_cast<QBertScene*>(pPrevScene);

				auto pGrid = pPrevQBertScene->GetHexGridObject()->GetComponent<HexGrid>();
				int diskScore = pGrid->GetRemainingDiskAmount() * (int)GameScore::SCORE_REMAINING_DISKS;

				auto pScoreComp = object->GetComponent<CharacterComponent>();
				if (pScoreComp)
					pWinningScene->SetFinalScore(pScoreComp->GetScore() + diskScore);		
			}
			dae::SceneManager::GetInstance().SetActiveScene(m_WinningSceneName);
		}
	}
}
