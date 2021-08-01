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
	Tonic::SceneManager::GetInstance().AddGameScene(std::make_shared<MainMenu>("Menu"));
	Tonic::SceneManager::GetInstance().AddGameScene(std::make_shared<LevelOne>("LevelOne"));
	Tonic::SceneManager::GetInstance().AddGameScene(std::make_shared<LevelTwo>("LevelTwo"));
	Tonic::SceneManager::GetInstance().AddGameScene(std::make_shared<LevelThree>("LevelThree"));
	Tonic::SceneManager::GetInstance().AddGameScene(std::make_shared<GameOverMenu>("GameOver"));
	Tonic::SceneManager::GetInstance().AddGameScene(std::make_shared<WinningGameMenu>("WinningGame"));
	Tonic::SceneManager::GetInstance().AddGameScene(std::make_shared<ControlsMenu>("ControlsMenu"));
	Tonic::SceneManager::GetInstance().SetActiveScene("Menu");
}
