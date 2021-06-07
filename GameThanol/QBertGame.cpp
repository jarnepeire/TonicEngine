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
#include "ControlsMenu.h"

using namespace Tonic;
QBertGame::QBertGame(uint32_t windowWidth, uint32_t windowHeight, float cappedFPS) 
	: BaseGameThanol(windowWidth, windowHeight, cappedFPS)
{
}

void QBertGame::CreateGameScenes()
{
	//Scene
	Tonic::SceneManager::GetInstance().AddGameScene(std::make_shared<MainMenu>("Menu", 0));
	Tonic::SceneManager::GetInstance().AddGameScene(std::make_shared<LevelOne>("LevelOne", 1));
	Tonic::SceneManager::GetInstance().AddGameScene(std::make_shared<LevelTwo>("LevelTwo", 2));
	Tonic::SceneManager::GetInstance().AddGameScene(std::make_shared<LevelThree>("LevelThree", 3));
	Tonic::SceneManager::GetInstance().AddGameScene(std::make_shared<GameOverMenu>("GameOver", 4));
	Tonic::SceneManager::GetInstance().AddGameScene(std::make_shared<WinningGameMenu>("WinningGame", 5));
	Tonic::SceneManager::GetInstance().AddGameScene(std::make_shared<ControlsMenu>("ControlsMenu", 6));
	Tonic::SceneManager::GetInstance().SetActiveScene("Menu");
}
