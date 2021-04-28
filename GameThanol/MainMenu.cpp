#include "MainMenu.h"
#include <InputManager.h>
#include "ToSceneCommand.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "RenderComponent.h"
#include <Renderer.h>
#include <ImageComponent.h>
#include "HexComponent.h"
#include "HexGrid.h"

using namespace dae;
MainMenu::MainMenu(const std::string& name, int idx)
	: Scene(name, idx)
{
}

void MainMenu::Initialize()
{
	auto& input = InputManager::GetInstance();
	input.AddInputAction((int)KeyboardButton::F2, ControllerButton::NULL_VALUE, ControllerButtonType::NULL_VALUE, TriggerState::Pressed, std::make_shared<ToSceneCommand>("QBert"));


	auto hexGrid = std::make_shared<GameObject>();
	hexGrid->SetPosition(125, 325);
	auto hexComp = hexGrid->AddComponent<HexGrid>(std::make_shared<HexGrid>(hexGrid.get(), "QBert/Block.png", 6, 64, 64));
	hexGrid->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(hexGrid.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	Add(hexGrid);


	auto topPos = hexComp->GetTop()->GetHexPosition();
	auto spriteObject = std::make_shared<GameObject>();
	spriteObject->SetPosition(topPos.x, topPos.y - 36);
	spriteObject->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(spriteObject.get(), "QBert/QBert_Spritesheet.png", 37, 36, 8, 125, 0.75f));
	spriteObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(spriteObject.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	Add(spriteObject);

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
