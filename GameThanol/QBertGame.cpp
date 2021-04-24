#include "QBertGame.h"
#include "SceneManager.h"
#include <memory>

#include "QBertScene.h"

void QBertGame::CreateGameScenes()
{
	//Scene
	//dae::SceneManager::GetInstance().AddScene(std::make_shared<QBertScene>("QBert", 0));
	//auto scene = SceneManager::GetInstance().GetCurrentScene();


	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<QBertScene>("QBert", 0));
	dae::SceneManager::GetInstance().SetActiveScene("QBert");
}
