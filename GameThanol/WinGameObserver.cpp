#include "WinGameObserver.h"
#include <GameObject.h>
#include "SceneManager.h"
#include "HexGrid.h"
#include "WinningGameMenu.h"
#include "QBertScene.h"
#include "GameScores.h"
#include "CharacterComponent.h"
#include "AudioLocator.h"
#include "GameEvent.h"

using namespace Tonic;
WinGameObserver::WinGameObserver(std::shared_ptr<HexGrid> currentLevelGrid, const std::string& winningSceneName, unsigned int winGameSoundId)
	: m_pGrid(currentLevelGrid)
	, m_WinningSceneName(winningSceneName)
	, m_WinGameSoundID(winGameSoundId)
{
}

void WinGameObserver::Notify(Tonic::GameObject* object, int eventId)
{
	if (eventId == (int)GameEvent::EVENT_JUMPER_LANDED)
	{
		//Pointer expired
		auto pGrid = m_pGrid.lock();
		if (!pGrid)
			return;

		if (pGrid->IsGridCompleted())
		{
			auto pScene = Tonic::SceneManager::GetInstance().GetScene(m_WinningSceneName);
			auto pWinningScene = dynamic_cast<WinningGameMenu*>(pScene);
			if (pWinningScene)
			{
				//Set final score
				auto pPrevScene = object->GetParentScene();
				auto pPrevQBertScene = dynamic_cast<QBertScene*>(pPrevScene);

				auto pGridPrev = pPrevQBertScene->GetHexGridObject()->GetComponent<HexGrid>();
				int diskScore = pGridPrev->GetRemainingDiskAmount() * (int)GameScore::SCORE_REMAINING_DISKS;

				auto pScoreComp = object->GetComponent<CharacterComponent>();
				if (pScoreComp)
					pWinningScene->SetFinalScore(pScoreComp->GetScore() + diskScore);		
			}

			AudioLocator::GetAudioSystem().Play(m_WinGameSoundID, 0.25f);
			Tonic::SceneManager::GetInstance().SetActiveScene(m_WinningSceneName);
		}
	}
}
