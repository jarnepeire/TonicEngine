#include "QBertScene.h"
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

using namespace dae;
QBertScene::QBertScene(const std::string& name, int idx)
	: Scene(name, idx)
	, m_pQBert()
{
}

void QBertScene::Initialize()
{
	auto qBertSmallFont = ResourceManager::GetInstance().LoadFont("CooperBlack.otf", 16);


	auto hexGrid = std::make_shared<GameObject>();
	hexGrid->SetPosition(125, 325);
	auto hexGridComp = hexGrid->AddComponent<HexGrid>(std::make_shared<HexGrid>(hexGrid.get(), "QBert/L1_Block.png", "QBert/L1_BlockVisitted.png", 6, 64, 64));
	hexGrid->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(hexGrid.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	Add(hexGrid);
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

	//QBert
	m_pQBert = std::make_shared<GameObject>();
	auto pSpriteComp = m_pQBert->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(m_pQBert.get(), "QBert/QBert_Spritesheet.png", 37, 36, 8, 125, 0.75f));
	pSpriteComp->SetLocalPosition(0, -36);
	m_pQBert->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(m_pQBert.get(), dae::Renderer::GetInstance().GetSDLRenderer()));

	auto pCharComp = m_pQBert->AddComponent<CharacterComponent>(std::make_shared<CharacterComponent>(m_pQBert.get()));
	pCharComp->GetSubject()->AddObserver(qBertScoreDisplay);

	auto pHealthComp = m_pQBert->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(m_pQBert.get(), 3));
	auto endGameObserver = std::make_shared<EndGameObserver>("GameOver");
	pHealthComp->GetSubject()->AddObserver(endGameObserver);
	pHealthComp->GetSubject()->AddObserver(qBertHealthDisplay);

	auto pRespawnComp = m_pQBert->AddComponent<RespawnComponent>(std::make_shared<RespawnComponent>(m_pQBert.get(), topPos, 3.0f));
	pHealthComp->SetRespawnComponent(pRespawnComp);
	m_pQBert->AddComponent<HexJumpComponent>(std::make_shared<HexJumpComponent>(m_pQBert.get(), hexGridComp.get(), 5, 0, 0.75f));
	Add(m_pQBert);

	//Input
	m_Input.AddInputAction((int)KeyboardButton::UP_ARROW, ControllerButton::ButtonY, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexTopRightCommand>(m_pQBert.get()));
	m_Input.AddInputAction((int)KeyboardButton::DOWN_ARROW, ControllerButton::ButtonA, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexBottomLeftCommand>(m_pQBert.get()));
	m_Input.AddInputAction((int)KeyboardButton::LEFT_ARROW, ControllerButton::ButtonX, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexTopLeftCommand>(m_pQBert.get()));
	m_Input.AddInputAction((int)KeyboardButton::RIGHT_ARROW, ControllerButton::ButtonB, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexBottomRightCommand>(m_pQBert.get()));

}

void QBertScene::FixedUpdate(float dt)
{
}

void QBertScene::Update(float dt)
{
}

void QBertScene::Render() const
{
}

void QBertScene::ResetLevel()
{
	m_pQBert->GetComponent<HexJumpComponent>()->ResetToTop();
	m_pQBert->GetComponent<HealthComponent>()->ResetLives();
	m_pQBert->GetComponent<CharacterComponent>()->ResetScore();
}
