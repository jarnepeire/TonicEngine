#include "EndGameObserver.h"
#include <GameObject.h>
#include "SceneManager.h"

EndGameObserver::EndGameObserver(const std::string& endGameSceneName)
	: m_EndGameSceneName(endGameSceneName)
{
}

void EndGameObserver::Notify(dae::GameObject* object, Event e)
{
	if (e == Event::EVENT_PLAYER_DIED)
	{
		dae::SceneManager::GetInstance().SetActiveScene(m_EndGameSceneName);
	}
}
