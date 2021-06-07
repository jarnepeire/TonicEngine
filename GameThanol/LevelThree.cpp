#include "LevelThree.h"
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

#include "HealthDisplay.h"
#include "ScoreDisplay.h"
#include "CharacterComponent.h"
#include "NextLevelObserver.h"
#include "AudioLocator.h"
#include <SDLAudio.h>
#include <LogAudio.h>

#include "DiskComponent.h"
#include "WinGameObserver.h"
#include "Colors.h"
#include "GameLevelInfo.h"
#include "QBertObserver.h"

#include <ColliderComponent.h>
#include "EnemyComponent.h"
#include "EnemyObserver.h"
#include "SamSlickComponent.h"
#include "SamSlickObserver.h"
#include "UggWrongwayComponent.h"
#include "UggWrongwayObserver.h"

using namespace Tonic;
LevelThree::LevelThree(const std::string& name, int idx)
	: QBertScene(name, idx, L"../Data/QBert/Levels/LevelThree.json")
{
}

void LevelThree::Initialize()
{
	auto qBertInfo = GetGameLevelInfo()->GetQBertInfo();
	auto levelInfo = GetGameLevelInfo()->GetLevelInfo();

	//Sound
	SDLAudio* pSDLAudio = new SDLAudio();
	unsigned int jumpSoundId = pSDLAudio->AddSound("../Data/QBert/Sounds/sfx_QBertJump.wav");
	unsigned int samSlickJumpSoundId = pSDLAudio->AddSound("../Data/QBert/Sounds/sfx_SlickSamJump.wav");
	unsigned int samSlickDeathSoundId = pSDLAudio->AddSound("../Data/QBert/Sounds/sfx_SlickSamDeath.wav");

	unsigned int uggWrongwayJumpSoundId = pSDLAudio->AddSound("../Data/QBert/Sounds/sfx_UggWrongwayJump.wav");
	unsigned int uggWrongwayDeathSoundId = pSDLAudio->AddSound("../Data/QBert/Sounds/sfx_UggWrongwayDeath.wav");

	unsigned int diedSoundId = pSDLAudio->AddSound("../Data/QBert/Sounds/sfx_Death.wav");
	unsigned int movingDiskSoundId = pSDLAudio->AddSound("../Data/QBert/Sounds/sfx_DiskMoving.wav");
	
	unsigned int endGameSoundId = pSDLAudio->AddSound("../Data/QBert/Sounds/sfx_EndGame.wav");
	unsigned int winGameSoundId = pSDLAudio->AddSound("../Data/QBert/Sounds/sfx_WinGame.wav");

	m_pAudioSytem = std::make_shared<LogAudio>(pSDLAudio);
	AudioLocator::RegisterAudioSystem(m_pAudioSytem.get());

	auto qBertSmallFont = ResourceManager::GetInstance().LoadFont("QBert/Fonts/CooperBlack.otf", 16);

	//UI
	//Player 1 Animation Text
	auto pPlayerUI = std::make_shared<GameObject>();
	pPlayerUI->SetPosition(30, 60);
	pPlayerUI->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
	pPlayerUI->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>("QBert/PlayerUI/PlayerOne_Spritesheet.png", 51, 7, 6, 100));
	auto pPlayerIcon = pPlayerUI->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("QBert/PlayerUI/PlayerOneIcon.png"));
	pPlayerIcon->SetLocalPosition(110, -7);
	Add(pPlayerUI);

	auto pLevelUI = std::make_shared<GameObject>();
	pLevelUI->SetPosition(30, 85);
	pLevelUI->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
	auto pLevelText = pLevelUI->AddComponent<TextComponent>(std::make_shared<TextComponent>("Level: 3", qBertSmallFont));
	pLevelText->SetColor(Colors::COLOR_TABLE[ColorName::DarkLimeGreen]);
	Add(pLevelUI);

	//Text object for display
	auto pPlayerInfo = std::make_shared<GameObject>();;
	pPlayerInfo->SetPosition(30, 110);
	pPlayerInfo->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));

	auto healthTextComp = pPlayerInfo->AddComponent<TextComponent>(std::make_shared<TextComponent>("Lives: 3", qBertSmallFont));
	healthTextComp->SetColor(Colors::COLOR_TABLE[ColorName::CottonCandyPink]);

	auto scoreTextComp = pPlayerInfo->AddComponent<TextComponent>(std::make_shared<TextComponent>("Score: 0", qBertSmallFont));
	scoreTextComp->SetLocalPosition(0, 25);
	scoreTextComp->SetColor(Colors::COLOR_TABLE[ColorName::VividOrange]);
	Add(pPlayerInfo);

	//Hex Grid
	m_pHexGridObject->SetPosition(100, 350);

	std::vector<std::string> hexImagePaths{};
	hexImagePaths.push_back("QBert/Props/BlockBlue.png");
	hexImagePaths.push_back("QBert/Props/BlockYellow.png");
	auto hexGridComp = m_pHexGridObject->AddComponent<HexGrid>(std::make_shared<HexGrid>(levelInfo.GridSize, 64, 64, levelInfo.NbVisits, hexImagePaths, levelInfo.IsAlternating));

	m_pHexGridObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
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
	auto endGameObserver = std::make_shared<EndGameObserver>("GameOver", endGameSoundId);
	auto pWinGameObserver = std::make_shared<WinGameObserver>(hexGridComp, "WinningGame", winGameSoundId);


	//QBert
	m_pQBert->SetDepthValue(-1.f);
	m_pQBert->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));

	auto pSpriteComp = m_pQBert->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>("QBert/Characters/QBert_Spritesheet.png", 37, 36, 8, 125, 0.6f));
	pSpriteComp->SetLocalPosition(8, -25);

	auto pCharComp = m_pQBert->AddComponent<CharacterComponent>(std::make_shared<CharacterComponent>());
	pCharComp->GetSubject()->AddObserver(qBertScoreDisplay);

	auto pHealthComp = m_pQBert->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(qBertInfo.Health));
	pHealthComp->GetSubject()->AddObserver(endGameObserver);
	pHealthComp->GetSubject()->AddObserver(qBertHealthDisplay);
	pHealthComp->GetSubject()->AddObserver(qBertObserver);

	auto pRespawnComp = m_pQBert->AddComponent<RespawnComponent>(std::make_shared<RespawnComponent>(topPos, 3.0f));
	pHealthComp->SetRespawnComponent(pRespawnComp);

	auto pHexJumpComp = m_pQBert->AddComponent<HexJumpComponent>(std::make_shared<HexJumpComponent>(hexGridComp.get(), levelInfo.GridSize - 1, 0, qBertInfo.JumpTime));
	pHexJumpComp->GetSubject()->AddObserver(qBertObserver);
	pHexJumpComp->GetSubject()->AddObserver(pWinGameObserver);

	auto pQBertCollider = m_pQBert->AddComponent<ColliderComponent>(std::make_shared<ColliderComponent>(CollisionLayer::Layer0, true, 16.f, 16.f));
	pQBertCollider->GetSubject()->AddObserver(qBertObserver);
	pQBertCollider->SetLocalPosition(8, -25);

	Add(m_pQBert);

	//Enemies
	//Enemy Observers
	auto pEnemyObserver = std::make_shared<EnemyObserver>(m_pQBert);
	auto pSamSlickObserver = std::make_shared<SamSlickObserver>(hexGridComp);
	auto pUggWrongwayObserver = std::make_shared<UggWrongwayObserver>(hexGridComp);

	//Sam
	m_pSam->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
	auto pSamSprite = m_pSam->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>("QBert/Characters/Sam_Spritesheet.png", 11, 16, 1, 100));
	pSamSprite->SetLocalPosition(18, -12);

	auto pSamEnemyComp = m_pSam->AddComponent<EnemyComponent>(std::make_shared<EnemyComponent>(EnemyType::SamSlick, 300, 5.f, 10.f, samSlickDeathSoundId));
	pSamEnemyComp->GetSubject()->AddObserver(pEnemyObserver);
	pSamEnemyComp->GetSubject()->AddObserver(pSamSlickObserver);

	m_pSam->AddComponent<HexJumpAIComponent>(std::make_shared<SamSlickComponent>(samSlickJumpSoundId));

	auto pSamHexJump = m_pSam->AddComponent<HexJumpComponent>(std::make_shared<HexJumpComponent>(hexGridComp.get(), levelInfo.GridSize - 2, 0, 0.7f));
	pSamHexJump->GetSubject()->AddObserver(pEnemyObserver);
	pSamHexJump->GetSubject()->AddObserver(pSamSlickObserver);

	auto pSamHealthComp = m_pSam->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(1));
	pSamHealthComp->GetSubject()->AddObserver(pEnemyObserver);

	auto pSamCollider = m_pSam->AddComponent<ColliderComponent>(std::make_shared<ColliderComponent>(CollisionLayer::Layer1, false, 10.f, 15.f));
	pSamCollider->SetLocalPosition(18, -12);

	Add(m_pSam);

	//Slick
	m_pSlick->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
	auto pSlickSprite = m_pSlick->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>("QBert/Characters/Slick_Spritesheet.png", 12, 16, 1, 100));
	pSlickSprite->SetLocalPosition(18, -12);

	auto pSlickEnemyComp = m_pSlick->AddComponent<EnemyComponent>(std::make_shared<EnemyComponent>(EnemyType::SamSlick, 300, 15.f, 25.f, samSlickDeathSoundId));
	pSlickEnemyComp->GetSubject()->AddObserver(pEnemyObserver);
	pSlickEnemyComp->GetSubject()->AddObserver(pSamSlickObserver);

	m_pSlick->AddComponent<HexJumpAIComponent>(std::make_shared<SamSlickComponent>(samSlickJumpSoundId));

	auto pSlickHexJump = m_pSlick->AddComponent<HexJumpComponent>(std::make_shared<HexJumpComponent>(hexGridComp.get(), levelInfo.GridSize - 2, 1, 0.7f));
	pSlickHexJump->GetSubject()->AddObserver(pEnemyObserver);
	pSlickHexJump->GetSubject()->AddObserver(pSamSlickObserver);

	auto pSlickHealthComp = m_pSlick->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(1));
	pSlickHealthComp->GetSubject()->AddObserver(pEnemyObserver);

	auto pSlickCollider = m_pSlick->AddComponent<ColliderComponent>(std::make_shared<ColliderComponent>(CollisionLayer::Layer1, false, 11.f, 15.f));
	pSlickCollider->SetLocalPosition(18, -12);

	Add(m_pSlick);

	//Ugg
	m_pUgg->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
	auto pUggSprite = m_pUgg->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>("QBert/Characters/Ugg_Spritesheet.png", 16, 16, 1, 100));
	pUggSprite->SetLocalPosition(35, 30);

	auto pUggEnemyComp = m_pUgg->AddComponent<EnemyComponent>(std::make_shared<EnemyComponent>(EnemyType::UggWrongway, 0, 2.f, 3.f, uggWrongwayDeathSoundId));
	pUggEnemyComp->GetSubject()->AddObserver(pEnemyObserver);
	pUggEnemyComp->GetSubject()->AddObserver(pUggWrongwayObserver);

	m_pUgg->AddComponent<HexJumpAIComponent>(std::make_shared<UggWrongwayComponent>(UggWrongwayComponent::UggWrongway::Ugg, uggWrongwayJumpSoundId));

	auto pUggHexJump = m_pUgg->AddComponent<HexJumpComponent>(std::make_shared<HexJumpComponent>(hexGridComp.get(), 0, levelInfo.GridSize - 1, 0.7f));
	pUggHexJump->GetSubject()->AddObserver(pEnemyObserver);
	pUggHexJump->GetSubject()->AddObserver(pUggWrongwayObserver);

	auto pUggHealthComp = m_pUgg->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(1));
	pUggHealthComp->GetSubject()->AddObserver(pEnemyObserver);

	auto pUggCollider = m_pUgg->AddComponent<ColliderComponent>(std::make_shared<ColliderComponent>(CollisionLayer::Layer1, false, 15.f, 15.f));
	pUggCollider->SetLocalPosition(35, 30);
	Add(m_pUgg);

	//Wrongway
	m_pWrongway->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
	auto pWrongwaySprite = m_pWrongway->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>("QBert/Characters/Wrongway_Spritesheet.png", 16, 16, 1, 100));
	pWrongwaySprite->SetLocalPosition(-8, 24);

	auto pWrongwayEnemyComp = m_pWrongway->AddComponent<EnemyComponent>(std::make_shared<EnemyComponent>(EnemyType::UggWrongway, 0, 5.f, 7.f, uggWrongwayDeathSoundId));
	pWrongwayEnemyComp->GetSubject()->AddObserver(pEnemyObserver);
	pWrongwayEnemyComp->GetSubject()->AddObserver(pUggWrongwayObserver);

	m_pWrongway->AddComponent<HexJumpAIComponent>(std::make_shared<UggWrongwayComponent>(UggWrongwayComponent::UggWrongway::Wrongway, uggWrongwayJumpSoundId));

	auto pWrongwayHexJump = m_pWrongway->AddComponent<HexJumpComponent>(std::make_shared<HexJumpComponent>(hexGridComp.get(), 0, 0, 0.7f));
	pWrongwayHexJump->GetSubject()->AddObserver(pEnemyObserver);
	pWrongwayHexJump->GetSubject()->AddObserver(pUggWrongwayObserver);

	auto pWrongwayHealthComp = m_pWrongway->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(1));
	pWrongwayHealthComp->GetSubject()->AddObserver(pEnemyObserver);

	auto pWrongwayCollider = m_pWrongway->AddComponent<ColliderComponent>(std::make_shared<ColliderComponent>(CollisionLayer::Layer1, false, 15.f, 15.f));
	pWrongwayCollider->SetLocalPosition(-8, 24);
	Add(m_pWrongway);

	//Input
	m_Input.AddInputAction((int)KeyboardButton::UP_ARROW, ControllerButton::ButtonDPAD_Up, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexTopRightCommand>(m_pQBert.get(), jumpSoundId, diedSoundId));
	m_Input.AddInputAction((int)KeyboardButton::DOWN_ARROW, ControllerButton::ButtonDPAD_Down, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexBottomLeftCommand>(m_pQBert.get(), jumpSoundId, diedSoundId));
	m_Input.AddInputAction((int)KeyboardButton::LEFT_ARROW, ControllerButton::ButtonDPAD_Left, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexTopLeftCommand>(m_pQBert.get(), jumpSoundId, diedSoundId));
	m_Input.AddInputAction((int)KeyboardButton::RIGHT_ARROW, ControllerButton::ButtonDPAD_Right, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexBottomRightCommand>(m_pQBert.get(), jumpSoundId, diedSoundId));

}

void LevelThree::FixedUpdate(float)
{
}

void LevelThree::Update(float)
{
}

void LevelThree::Render() const
{
}

void LevelThree::ResetLevel()
{
	m_pQBert->GetComponent<HexJumpComponent>()->ResetToTop();
	m_pQBert->GetComponent<HealthComponent>()->ResetLives();
	m_pQBert->GetComponent<CharacterComponent>()->ResetScore();
	m_pQBert->GetComponent<SpriteComponent>()->SetAnimationRow(0);
	m_pQBert->GetComponent<SpriteComponent>()->SetIsFlipped(false);

	m_pSam->GetComponent<HexJumpComponent>()->ResetToOriginalCoordinate();
	m_pSam->GetComponent<EnemyComponent>()->ResetEnemy();
	m_pSam->GetComponent<HexJumpAIComponent>()->ResetAI();
	m_pSam->GetComponent<SpriteComponent>()->SetAnimationRow(0);
	m_pSam->GetComponent<SpriteComponent>()->SetIsFlipped(false);

	m_pSlick->GetComponent<HexJumpComponent>()->ResetToOriginalCoordinate();
	m_pSlick->GetComponent<EnemyComponent>()->ResetEnemy();
	m_pSlick->GetComponent<HexJumpAIComponent>()->ResetAI();
	m_pSlick->GetComponent<SpriteComponent>()->SetAnimationRow(0);
	m_pSlick->GetComponent<SpriteComponent>()->SetIsFlipped(false);

	m_pUgg->GetComponent<HexJumpComponent>()->ResetToOriginalCoordinate();
	m_pUgg->GetComponent<EnemyComponent>()->ResetEnemy();
	m_pUgg->GetComponent<HexJumpAIComponent>()->ResetAI();
	m_pUgg->GetComponent<SpriteComponent>()->SetAnimationRow(0);
	m_pUgg->GetComponent<SpriteComponent>()->SetIsFlipped(true);

	m_pWrongway->GetComponent<HexJumpComponent>()->ResetToOriginalCoordinate();
	m_pWrongway->GetComponent<EnemyComponent>()->ResetEnemy();
	m_pWrongway->GetComponent<HexJumpAIComponent>()->ResetAI();
	m_pWrongway->GetComponent<SpriteComponent>()->SetAnimationRow(0);
	m_pWrongway->GetComponent<SpriteComponent>()->SetIsFlipped(true);

	m_pHexGridObject->GetComponent<HexGrid>()->ResetGrid();

	for (unsigned int i = 0; i < m_NbDisks; ++i)
	{
		auto pDisk = m_pDisks[i]->GetComponent<DiskComponent>();
		pDisk->AttachToGrid(m_pHexGridObject->GetComponent<HexGrid>(), m_DiskHexCoordinates[i]);
	}
}
