#include "QBertGame.h"
#include "SceneManager.h"
#include <memory>

#include "QBertScene.h"
#include "MainMenu.h"
#include "GameOverMenu.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "WinningGameMenu.h"

using namespace dae;
QBertGame::QBertGame(uint32_t windowWidth, uint32_t windowHeight, float cappedFPS) 
	: BaseGameThanol(windowWidth, windowHeight, cappedFPS)
{
}

void QBertGame::CreateGameScenes()
{
	//Scene
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<MainMenu>("Menu", 0));
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<LevelOne>("LevelOne", 1));
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<LevelTwo>("LevelTwo", 2));
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<LevelThree>("LevelThree", 3));
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<GameOverMenu>("GameOver", 4));
	dae::SceneManager::GetInstance().AddGameScene(std::make_shared<WinningGameMenu>("WinningGame", 5));
	dae::SceneManager::GetInstance().SetActiveScene("Menu");
}
