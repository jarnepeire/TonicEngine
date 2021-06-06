#include "LevelOne.h"
#include <InputManager.h>
#include "GameObject.h"
#include "SpriteComponent.h"
#include "RenderComponent.h"
#include <Renderer.h>
#include <ImageComponent.h>
#include "HexComponent.h"
#include "HexJumpComponent.h"
#include "HexGrid.h"
#include "JumpToHexCommand.h"
#include "RespawnComponent.h"
#include "HealthComponent.h"
#include "EndGameObserver.h"
#include <TextComponent.h>
#include "ResourceManager.h"

#include <HealthDisplay.h>
#include <ScoreDisplay.h>
#include "CharacterComponent.h"
#include "NextLevelObserver.h"
#include "AudioLocator.h"
#include <SDLAudio.h>
#include <LogAudio.h>
#include "DiskComponent.h"
#include "Colors.h"

#include "GameLevelInfo.h"
#include "HexJumpAIComponent.h"
#include "EnemyComponent.h"
#include "EnemyObserver.h"
#include "SamSlickComponent.h"
#include "QBertObserver.h"
#include "SamSlickObserver.h"
#include "ColliderComponent.h"

using namespace dae;
LevelOne::LevelOne(const std::string& name, int idx)
	: QBertScene(name, idx, L"../Data/QBert/Levels/LevelOne.json")
{
}

void LevelOne::Initialize()
{
	auto qBertInfo = GetGameLevelInfo()->GetQBertInfo();
	auto levelInfo = GetGameLevelInfo()->GetLevelInfo();

	//Sound
	SDLAudio* pSDLAudio = new SDLAudio();
	unsigned int jumpSoundId = pSDLAudio->AddSound("../Data/Sounds/sfx_QBertJump.wav");
	unsigned int samSlickJumpSoundId = pSDLAudio->AddSound("../Data/Sounds/sfx_SlickSamJump.wav");
	unsigned int scoreSoundId = pSDLAudio->AddSound("../Data/Sounds/sfx_gain_score.wav");
	unsigned int diedSoundId = pSDLAudio->AddSound("../Data/Sounds/sfx_Death.wav");
	unsigned int movingDiskSoundId = pSDLAudio->AddSound("../Data/Sounds/sfx_DiskMoving.wav");

	m_pAudioSytem = std::make_shared<LogAudio>(pSDLAudio);
	AudioLocator::RegisterAudioSystem(m_pAudioSytem.get());

	//Font
	auto qBertSmallFont = ResourceManager::GetInstance().LoadFont("CooperBlack.otf", 16);

	//UI
	//Player 1 Animation Text
	auto pPlayerUI = std::make_shared<GameObject>();
	pPlayerUI->SetPosition(30, 60);
	pPlayerUI->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(pPlayerUI.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	pPlayerUI->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(pPlayerUI.get(), "QBert/PlayerOne_Spritesheet.png", 51, 7, 6, 100));
	auto pPlayerIcon = pPlayerUI->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(pPlayerUI.get(), "QBert/PlayerOneIcon.png"));
	pPlayerIcon->SetLocalPosition(110, -7);
	Add(pPlayerUI);

	auto pLevelUI = std::make_shared<GameObject>();
	pLevelUI->SetPosition(30, 85);
	pLevelUI->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(pLevelUI.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	auto pLevelText = pLevelUI->AddComponent<TextComponent>(std::make_shared<TextComponent>(pLevelUI.get(), "Level: 1", qBertSmallFont));
	pLevelText->SetColor(Colors::COLOR_TABLE[ColorName::DarkLimeGreen]);
	Add(pLevelUI);

	//Text object for display
	auto pPlayerInfo = std::make_shared<GameObject>();;
	pPlayerInfo->SetPosition(30, 110);
	pPlayerInfo->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(pPlayerInfo.get(), dae::Renderer::GetInstance().GetSDLRenderer()));

	auto healthTextComp = pPlayerInfo->AddComponent<TextComponent>(std::make_shared<TextComponent>(pPlayerInfo.get(), "Lives: 3", qBertSmallFont));
	healthTextComp->SetColor(Colors::COLOR_TABLE[ColorName::CottonCandyPink]);

	auto scoreTextComp = pPlayerInfo->AddComponent<TextComponent>(std::make_shared<TextComponent>(pPlayerInfo.get(), "Score: 0", qBertSmallFont));
	scoreTextComp->SetLocalPosition(0, 25);
	scoreTextComp->SetColor(Colors::COLOR_TABLE[ColorName::VividOrange]);
	Add(pPlayerInfo);

	//HexGrid
	m_pHexGridObject->SetPosition(100, 350);

	std::vector<std::string> hexImagePaths{};
	hexImagePaths.push_back("QBert/L1_Block.png");
	hexImagePaths.push_back("QBert/L1_BlockVisited.png");
	auto hexGridComp = m_pHexGridObject->AddComponent<HexGrid>(std::make_shared<HexGrid>(m_pHexGridObject.get(), levelInfo.GridSize, 64, 64, levelInfo.NbVisits, hexImagePaths, levelInfo.IsAlternating));

	m_pHexGridObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(m_pHexGridObject.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	Add(m_pHexGridObject);
	auto topPos = hexGridComp->GetTop()->GetHexPosition();

	//Disks
	for (auto& diskCoordinate : levelInfo.DiskCoordinates)
	{
		AddDiskToGrid(hexGridComp, diskCoordinate, movingDiskSoundId);
	}

	//Observer -> link up the text components to display to (doesn't own two text components in this case)
	auto qBertHealthDisplay = std::make_shared<HealthDisplay>(healthTextComp);
	auto qBertScoreDisplay = std::make_shared<ScoreDisplay>(scoreTextComp);

	auto qBertObserver = std::make_shared<QBertObserver>(hexGridComp, m_pQBert);
	auto endGameObserver = std::make_shared<EndGameObserver>("GameOver");
	auto pNextLevelObserver = std::make_shared<NextLevelObserver>(hexGridComp, "LevelTwo");


	//QBert
	m_pQBert->SetDepthValue(-1.f);
	m_pQBert->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(m_pQBert.get(), dae::Renderer::GetInstance().GetSDLRenderer()));

	auto pSpriteComp = m_pQBert->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(m_pQBert.get(), "QBert/QBert_Spritesheet.png", 37, 36, 8, 125, 0.75f));
	pSpriteComp->SetLocalPosition(0, -36);

	auto pCharComp = m_pQBert->AddComponent<CharacterComponent>(std::make_shared<CharacterComponent>(m_pQBert.get()));
	pCharComp->GetSubject()->AddObserver(qBertScoreDisplay);

	auto pHealthComp = m_pQBert->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(m_pQBert.get(), qBertInfo.Health));
	pHealthComp->GetSubject()->AddObserver(endGameObserver);
	pHealthComp->GetSubject()->AddObserver(qBertHealthDisplay);

	auto pRespawnComp = m_pQBert->AddComponent<RespawnComponent>(std::make_shared<RespawnComponent>(m_pQBert.get(), topPos, 3.0f));
	pHealthComp->SetRespawnComponent(pRespawnComp);

	auto pHexJumpComp = m_pQBert->AddComponent<HexJumpComponent>(std::make_shared<HexJumpComponent>(m_pQBert.get(), hexGridComp.get(), levelInfo.GridSize - 1, 0, qBertInfo.JumpTime));
	pHexJumpComp->GetSubject()->AddObserver(qBertObserver);
	pHexJumpComp->GetSubject()->AddObserver(pNextLevelObserver);

	auto pQBertCollider = m_pQBert->AddComponent<ColliderComponent>(std::make_shared<ColliderComponent>(m_pQBert.get(), CollisionLayer::Layer0, true, 10.f, 10.f));
	pQBertCollider->GetSubject()->AddObserver(qBertObserver);

	Add(m_pQBert);

	//Enemies
	//Enemy Observers
	auto pEnemyObserver = std::make_shared<EnemyObserver>(m_pQBert);
	auto pSamSlickObserver = std::make_shared<SamSlickObserver>(hexGridComp);

	//Sam
	m_pSam->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(m_pSam.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	auto pSamSprite = m_pSam->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(m_pSam.get(), "QBert/Sam_Spritesheet.png", 11, 16, 1, 100));
	pSamSprite->SetLocalPosition(18, -9.5);

	auto pSamEnemyComp = m_pSam->AddComponent<EnemyComponent>(std::make_shared<EnemyComponent>(m_pSam.get(), EnemyComponent::EnemyType::SamSlick, 300, 5.f, 10.f));
	pSamEnemyComp->GetSubject()->AddObserver(pEnemyObserver);
	pSamEnemyComp->GetSubject()->AddObserver(pSamSlickObserver);

	m_pSam->AddComponent<HexJumpAIComponent>(std::make_shared<SamSlickComponent>(m_pSam.get(), samSlickJumpSoundId));

	auto pSamHexJump = m_pSam->AddComponent<HexJumpComponent>(std::make_shared<HexJumpComponent>(m_pSam.get(), hexGridComp.get(), levelInfo.GridSize - 2, 0, 0.7f));
	pSamHexJump->GetSubject()->AddObserver(pEnemyObserver);
	pSamHexJump->GetSubject()->AddObserver(pSamSlickObserver);

	auto pSamHealthComp = m_pSam->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(m_pSam.get(), 1));
	pSamHealthComp->GetSubject()->AddObserver(pEnemyObserver);

	auto pSamCollider = m_pSam->AddComponent<ColliderComponent>(std::make_shared<ColliderComponent>(m_pSam.get(), CollisionLayer::Layer1, false, 10.f, 10.f));

	Add(m_pSam);

	//Slick
	m_pSlick->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(m_pSlick.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	auto pSlickSprite = m_pSlick->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(m_pSlick.get(), "QBert/Slick_Spritesheet.png", 12, 16, 1, 100));
	pSlickSprite->SetLocalPosition(18, -9.5);

	auto pSlickEnemyComp = m_pSlick->AddComponent<EnemyComponent>(std::make_shared<EnemyComponent>(m_pSlick.get(), EnemyComponent::EnemyType::SamSlick, 300, 15.f, 25.f));
	pSlickEnemyComp->GetSubject()->AddObserver(pEnemyObserver);
	pSlickEnemyComp->GetSubject()->AddObserver(pSamSlickObserver);

	m_pSlick->AddComponent<HexJumpAIComponent>(std::make_shared<SamSlickComponent>(m_pSlick.get(), samSlickJumpSoundId));

	auto pSlickHexJump = m_pSlick->AddComponent<HexJumpComponent>(std::make_shared<HexJumpComponent>(m_pSlick.get(), hexGridComp.get(), levelInfo.GridSize - 2, 1, 0.7f));
	pSlickHexJump->GetSubject()->AddObserver(pEnemyObserver);
	pSlickHexJump->GetSubject()->AddObserver(pSamSlickObserver);

	auto pSlickHealthComp = m_pSlick->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(m_pSlick.get(), 1));
	pSlickHealthComp->GetSubject()->AddObserver(pEnemyObserver);

	auto pSlickCollider = m_pSlick->AddComponent<ColliderComponent>(std::make_shared<ColliderComponent>(m_pSlick.get(), CollisionLayer::Layer1, false, 10.f, 10.f));
	Add(m_pSlick);

	//Input
	m_Input.AddInputAction((int)KeyboardButton::UP_ARROW, ControllerButton::ButtonDPAD_Up, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexTopRightCommand>(m_pQBert.get(), jumpSoundId, diedSoundId));
	m_Input.AddInputAction((int)KeyboardButton::DOWN_ARROW, ControllerButton::ButtonDPAD_Down, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexBottomLeftCommand>(m_pQBert.get(), jumpSoundId, diedSoundId));
	m_Input.AddInputAction((int)KeyboardButton::LEFT_ARROW, ControllerButton::ButtonDPAD_Left, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexTopLeftCommand>(m_pQBert.get(), jumpSoundId, diedSoundId));
	m_Input.AddInputAction((int)KeyboardButton::RIGHT_ARROW, ControllerButton::ButtonDPAD_Right, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexBottomRightCommand>(m_pQBert.get(), jumpSoundId, diedSoundId));


	//m_Input.AddInputAction((int)KeyboardButton::A, ControllerButton::ButtonA, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<ScoreCommand>(m_pQBert.get(), scoreSoundId));
	//m_Input.AddInputAction((int)KeyboardButton::B, ControllerButton::ButtonB, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<DieCommand>(m_pQBert.get(), diedSoundId));

}

void LevelOne::FixedUpdate(float dt)
{
}

void LevelOne::Update(float dt)
{
}

void LevelOne::Render() const
{
}

void LevelOne::ResetLevel()
{
	m_pQBert->GetComponent<HexJumpComponent>()->ResetToTop();
	m_pQBert->GetComponent<HealthComponent>()->ResetLives();
	m_pQBert->GetComponent<CharacterComponent>()->ResetScore();
	m_pQBert->GetComponent<SpriteComponent>()->SetAnimationRow(0);
	m_pQBert->GetComponent<SpriteComponent>()->SetIsLeft(false);
	
	m_pSam->GetComponent<HexJumpComponent>()->ResetToOriginalCoordinate();
	m_pSam->GetComponent<EnemyComponent>()->ResetEnemy();
	m_pSam->GetComponent<HexJumpAIComponent>()->ResetAI();
	m_pSam->GetComponent<SpriteComponent>()->SetAnimationRow(0);
	m_pSam->GetComponent<SpriteComponent>()->SetIsLeft(false);

	m_pSlick->GetComponent<HexJumpComponent>()->ResetToOriginalCoordinate();
	m_pSlick->GetComponent<EnemyComponent>()->ResetEnemy();
	m_pSlick->GetComponent<HexJumpAIComponent>()->ResetAI();
	m_pSlick->GetComponent<SpriteComponent>()->SetAnimationRow(0);
	m_pSlick->GetComponent<SpriteComponent>()->SetIsLeft(false);

	m_pHexGridObject->GetComponent<HexGrid>()->ResetGrid();

	for (unsigned int i = 0; i < m_NbDisks; ++i)
	{
		auto pDisk = m_pDisks[i]->GetComponent<DiskComponent>();
		pDisk->AttachToGrid(m_pHexGridObject->GetComponent<HexGrid>(), m_DiskHexCoordinates[i]);
	}


}