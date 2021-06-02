#include "WinGameObserver.h"
#include <GameObject.h>
#include "SceneManager.h"

WinGameObserver::WinGameObserver(const std::string& winningSceneName)
	: m_WinningSceneName(winningSceneName)
{
}

void WinGameObserver::Notify(dae::GameObject* object, Event e)
{
	if (e == Event::EVENT_PLAYER_LANDED)
	{

		dae::SceneManager::GetInstance().SetActiveScene(m_WinningSceneName);
	}
}
