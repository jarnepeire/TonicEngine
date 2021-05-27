#include "MainMenu.h"
#include <InputManager.h>
#include "ToSceneCommand.h"
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

using namespace dae;
MainMenu::MainMenu(const std::string& name, int idx)
	: Scene(name, idx)
{
}

void MainMenu::Initialize()
{


	auto hexGrid = std::make_shared<GameObject>();
	hexGrid->SetPosition(125, 325);
	auto hexGridComp = hexGrid->AddComponent<HexGrid>(std::make_shared<HexGrid>(hexGrid.get(), "QBert/Block.png", 6, 64, 64));
	hexGrid->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(hexGrid.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	Add(hexGrid);


	auto topPos = hexGridComp->GetTop()->GetHexPosition();
	auto spriteObject = std::make_shared<GameObject>();
	auto pSpriteComp = spriteObject->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(spriteObject.get(), "QBert/QBert_Spritesheet.png", 37, 36, 8, 125, 0.75f));
	pSpriteComp->SetLocalPosition(0, -36);
	spriteObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(spriteObject.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	auto pHealthComp = spriteObject->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(spriteObject.get(), 5));
	auto pRespawnComp = spriteObject->AddComponent<RespawnComponent>(std::make_shared<RespawnComponent>(spriteObject.get(), topPos, 3.0f));
	pHealthComp->SetRespawnComponent(pRespawnComp);
	spriteObject->AddComponent<HexJumpComponent>(std::make_shared<HexJumpComponent>(spriteObject.get(), hexGridComp.get(), 5, 0, 0.75f));
	Add(spriteObject);

	//Input
	m_Input.AddInputAction((int)KeyboardButton::F2, ControllerButton::NULL_VALUE, ControllerButtonType::NULL_VALUE, TriggerState::Pressed, std::make_shared<ToSceneCommand>("QBert"));
	m_Input.AddInputAction((int)KeyboardButton::UP_ARROW, ControllerButton::ButtonY, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexTopRightCommand>(spriteObject.get()));
	m_Input.AddInputAction((int)KeyboardButton::DOWN_ARROW, ControllerButton::ButtonA, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexBottomLeftCommand>(spriteObject.get()));
	m_Input.AddInputAction((int)KeyboardButton::LEFT_ARROW, ControllerButton::ButtonX, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexTopLeftCommand>(spriteObject.get()));
	m_Input.AddInputAction((int)KeyboardButton::RIGHT_ARROW, ControllerButton::ButtonB, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<JumpToHexBottomRightCommand>(spriteObject.get()));

}

void MainMenu::FixedUpdate(float dt)
{
}

void MainMenu::Update(float dt)
{
}

void MainMenu::Render() const
{
}
