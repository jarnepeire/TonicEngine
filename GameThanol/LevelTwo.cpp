#include "LevelTwo.h"
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
#include "QBertAnimationObserver.h"
#include "AudioLocator.h"
#include <SDLAudio.h>
#include <LogAudio.h>

using namespace dae;
LevelTwo::LevelTwo(const std::string& name, int idx)
	: Scene(name, idx)
	, m_pQBert()
	, m_pHexGridObject()
{
}

void LevelTwo::Initialize()
{
	//Sound
	SDLAudio* pSDLAudio = new SDLAudio();
	int jumpSoundId = pSDLAudio->AddSound("../Data/Sounds/sfx_QBertJump.wav");

	m_pAudioSytem = std::make_shared<LogAudio>(pSDLAudio);
	AudioLocator::RegisterAudioSystem(m_pAudioSytem.get());

	//Level
	auto qBertSmallFont = ResourceManager::GetInstance().LoadFont("CooperBlack.otf", 16);


	m_pHexGridObject = std::make_shared<GameObject>();
	m_pHexGridObject->SetPosition(125, 325);

	//std::vector<std::string> hexImagePaths{};
	//hexImagePaths.push_back("QBert/L1_Block.png");
	//hexImagePaths.push_back("QBert/L1_BlockVisited.png");
	//auto hexGridComp = m_pHexGridObject->AddComponent<HexGrid>(std::make_shared<HexGrid>(m_pHexGridObject.get(), 6, 64, 64, 1, hexImagePaths));

	std::vector<std::string> hexImagePaths{};
	hexImagePaths.push_back("QBert/L2_Block.png");
	hexImagePaths.push_back("QBert/L2_BlockIntermediate.png");
	hexImagePaths.push_back("QBert/L2_BlockVisited.png");
	auto hexGridComp = m_pHexGridObject->AddComponent<HexGrid>(std::make_shared<HexGrid>(m_pHexGridObject.get(), 6, 64, 64, 2, hexImagePaths));

	//std::vector<std::string> hexImagePaths{};
	//hexImagePaths.push_back("QBert/L1_Block.png");
	//hexImagePaths.push_back("QBert/L1_BlockVisited.png");
	//auto hexGridComp = m_pHexGridObject->AddComponent<HexGrid>(std::make_shared<HexGrid>(m_pHexGridObject.get(), 6, 64, 64, hexImagePaths));


	m_pHexGridObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(m_pHexGridObject.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	Add(m_pHexGridObject);
	auto topPos = hexGridComp->GetTop()->GetHexPosition();


	//Text object for display
	auto pDisplay = std::make_shared<GameObject>();;
	pDisplay->SetPosition(30, 100);
	pDisplay->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(pDisplay.get(), dae::Renderer::GetInstance().GetSDLRenderer()));

	auto healthTextComp = pDisplay->AddComponent<TextComponent>(std::make_shared<TextComponent>(pDisplay.get(), "Lives: 3", qBertSmallFont));
	healthTextComp->SetLocalPosition(0, 30); //Servers a translation relative to the parent object
	auto scoreTextComp = pDisplay->AddComponent<TextComponent>(std::make_shared<TextComponent>(pDisplay.get(), "Score: 0", qBertSmallFont));
	scoreTextComp->SetLocalPosition(0, 55); //Servers a translation relative to the parent object
	Add(pDisplay);

	//Observer -> link up the text components to display to (doesn't own two text components in this case)
	auto qBertHealthDisplay = std::make_shared<HealthDisplay>(healthTextComp);
	auto qBertScoreDisplay = std::make_shared<ScoreDisplay>(scoreTextComp);
	auto qBertAnimation = std::make_shared<QBertAnimationObserver>();
	auto endGameObserver = std::make_shared<EndGameObserver>("GameOver");

	//QBert
	m_pQBert = std::make_shared<GameObject>();
	m_pQBert->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(m_pQBert.get(), dae::Renderer::GetInstance().GetSDLRenderer()));

	auto pSpriteComp = m_pQBert->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(m_pQBert.get(), "QBert/QBert_Spritesheet.png", 37, 36, 8, 125, 0.75f));
	pSpriteComp->SetLocalPosition(0, -36);
	qBertAnimation->SetSpriteComponent(pSpriteComp);

	auto pCharComp = m_pQBert->AddComponent<CharacterComponent>(std::make_shared<CharacterComponent>(m_pQBert.get()));
	pCharComp->GetSubject()->AddObserver(qBertScoreDisplay);

	auto pHealthComp = m_pQBert->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(m_pQBert.get(), 3));
	pHealthComp->GetSubject()->AddObserver(endGameObserver);
	pHealthComp->GetSubject()->AddObserver(qBertHealthDisplay);
	pHealthComp->GetSubject()->AddObserver(qBertAnimation);

	auto pRespawnComp = m_pQBert->AddComponent<RespawnComponent>(std::make_shared<RespawnComponent>(m_pQBert.get(), topPos, 3.0f));
	pHealthComp->SetRespawnComponent(pRespawnComp);

	auto pHexJumpComp = m_pQBert->AddComponent<HexJumpComponent>(std::make_shared<HexJumpComponent>(m_pQBert.get(), hexGridComp.get(), 5, 0, 0.75f));
	pHexJumpComp->GetSubject()->AddObserver(qBertAnimation);

	Add(m_pQBert);

	//Input
	m_Input.AddInputAction((int)KeyboardButton::UP_ARROW, ControllerButton::ButtonY, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexTopRightCommand>(m_pQBert.get(), jumpSoundId));
	m_Input.AddInputAction((int)KeyboardButton::DOWN_ARROW, ControllerButton::ButtonA, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexBottomLeftCommand>(m_pQBert.get(), jumpSoundId));
	m_Input.AddInputAction((int)KeyboardButton::LEFT_ARROW, ControllerButton::ButtonX, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexTopLeftCommand>(m_pQBert.get(), jumpSoundId));
	m_Input.AddInputAction((int)KeyboardButton::RIGHT_ARROW, ControllerButton::ButtonB, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexBottomRightCommand>(m_pQBert.get(), jumpSoundId));

}

void LevelTwo::FixedUpdate(float dt)
{
}

void LevelTwo::Update(float dt)
{
}

void LevelTwo::Render() const
{
}

void LevelTwo::ResetLevel()
{
	m_pQBert->GetComponent<HexJumpComponent>()->ResetToTop();
	m_pQBert->GetComponent<HealthComponent>()->ResetLives();
	m_pQBert->GetComponent<CharacterComponent>()->ResetScore();
	m_pHexGridObject->GetComponent<HexGrid>()->ResetGrid();
}
