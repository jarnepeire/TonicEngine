#include "NextLevelObserver.h"
#include "HexGrid.h"
#include "SceneManager.h"

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
			dae::SceneManager::GetInstance().SetActiveScene(m_NextLevelName);
		}
	}
}
