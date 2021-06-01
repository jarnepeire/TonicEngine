#include "QBertGame.h"
#include "SceneManager.h"
#include <memory>

#include "QBertScene.h"
#include "MainMenu.h"
#include "GameOverMenu.h"
#include "LevelTwo.h"

using namespace dae;
QBertGame::QBertGame(uint32_t windowWidth, uint32_t windowHeight, float cappedFPS) 
	: BaseGameThanol(windowWidth, windowHeight, cappedFPS)
{
}

void QBertGame::CreateGameScenes()
{
	//Scene
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<MainMenu>("Menu", 0));
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<QBertScene>("QBert", 1));
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<LevelTwo>("LevelTwo", 2));
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<GameOverMenu>("GameOver", 3));
	dae::SceneManager::GetInstance().SetActiveScene("Menu");
}
