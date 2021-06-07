#include "NextLevelObserver.h"
#include "HexGrid.h"
#include "SceneManager.h"
#include "QBertScene.h"
#include <GameObject.h>
#include "HealthComponent.h"
#include "CharacterComponent.h"
#include "GameScores.h"
#include "AudioLocator.h"
#include "GameEvent.h"

using namespace Tonic;
NextLevelObserver::NextLevelObserver(std::shared_ptr<HexGrid> currentLevelGrid, const std::string& nextLevelName, unsigned int nextLevelSoundId)
	: m_pGrid(currentLevelGrid)
	, m_NextLevelName(nextLevelName)
	, m_NextLevelSoundID(nextLevelSoundId)
{
}

void NextLevelObserver::Notify(Tonic::GameObject* object, int eventId)
{
	if (eventId == (int)GameEvent::EVENT_JUMPER_LANDED)
	{
		//Pointer expired
		auto pGrid = m_pGrid.lock();
		if (!pGrid)
			return;

		if (pGrid->IsGridCompleted())
		{
			auto pScene = Tonic::SceneManager::GetInstance().GetScene(m_NextLevelName);
			auto pNextQBertScene = dynamic_cast<QBertScene*>(pScene);
			if (pNextQBertScene)
			{
				//Clear next scene
				pNextQBertScene->ResetLevel();

				//Set starting variables depending on previous scene
				auto pPrevScene = object->GetParentScene();
				auto pPrevQBertScene = dynamic_cast<QBertScene*>(pPrevScene);

				auto pGrid = pPrevQBertScene->GetHexGridObject()->GetComponent<HexGrid>();
				int diskScore = pGrid->GetRemainingDiskAmount() * (int)GameScore::SCORE_REMAINING_DISKS;

				auto pScoreComp = object->GetComponent<CharacterComponent>();
				if (pScoreComp)
					pNextQBertScene->SetStartScore(pScoreComp->GetScore() + diskScore);

				auto pHealthComp = object->GetComponent<HealthComponent>();
				if (pHealthComp)
					pNextQBertScene->SetStartLives(pHealthComp->GetNbLives());

				//Clear previous scene
				pPrevQBertScene->ResetLevel();
			}

			AudioLocator::GetAudioSystem().Play(m_NextLevelSoundID, 0.25f);
			Tonic::SceneManager::GetInstance().SetActiveScene(m_NextLevelName);
		}
	}
}
