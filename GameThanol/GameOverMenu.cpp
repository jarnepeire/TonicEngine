#include "GameOverMenu.h"
#include <GameObject.h>
#include <RenderComponent.h>
#include <TextComponent.h>
#include <Renderer.h>
#include <ResourceManager.h>

using namespace dae;
GameOverMenu::GameOverMenu(const std::string& name, int idx)
	: dae::Scene(name, idx)
{
}

void GameOverMenu::Initialize()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto pEndText = std::make_shared<GameObject>();;
	pEndText->SetPosition(30, 250);

	pEndText->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(pEndText.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	pEndText->AddComponent<TextComponent>(std::make_shared<TextComponent>(pEndText.get(), "Game Over!", font));
	Add(pEndText);
}

void GameOverMenu::FixedUpdate(float dt)
{
}

void GameOverMenu::Update(float dt)
{
}

void GameOverMenu::Render() const
{
}
