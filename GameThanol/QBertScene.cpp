#include "QBertScene.h"
#include <InputManager.h>
#include <ResourceManager.h>

#include <GameObject.h>
#include <Scene.h>
#include <Renderer.h>
#include <KeyboardMapping.h>

//Sound
#include "AudioLocator.h"
#include "SDLAudio.h"
#include "LogAudio.h"

//Commands
#include "Command.h"

//Observers
#include <HealthDisplay.h>
#include <ScoreDisplay.h>

//Components
#include <FPSComponent.h>
#include <TextComponent.h>
#include <RenderComponent.h>
#include <ImageComponent.h>
#include <HealthComponent.h>
#include <CharacterComponent.h>

using namespace dae;
QBertScene::QBertScene(const std::string& name, int idx)
	: Scene(name, idx)
{
}

void QBertScene::Initialize()
{
	auto& input = InputManager::GetInstance();

	//Fonts
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);
	auto qBertBigFont = ResourceManager::GetInstance().LoadFont("CooperBlack.otf", 28);
	auto qBertSmallFont = ResourceManager::GetInstance().LoadFont("CooperBlack.otf", 22);

	//Background
	auto bgObject = std::make_shared<GameObject>();
	bgObject->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(bgObject.get(), "background.jpg"));
	bgObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(bgObject.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	Add(bgObject);

	//Logo
	auto logoObject = std::make_shared<GameObject>();
	logoObject->SetPosition(216, 180);
	logoObject->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(logoObject.get(), "logo.png"));
	logoObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(logoObject.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	Add(logoObject);

	//Header text
	auto to = std::make_shared<GameObject>();
	to->SetPosition(80, 20);
	to->AddComponent<TextComponent>(std::make_shared<TextComponent>(to.get(), "Programming 4 Assignment", font));
	to->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(to.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	Add(to);

	//FPS game object
	auto fpsCounter = std::make_shared<GameObject>();
	fpsCounter->SetPosition(30, 15);
	fpsCounter->AddComponent<FPSComponent>(std::make_shared<FPSComponent>(fpsCounter.get(), fpsFont));
	fpsCounter->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(fpsCounter.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	Add(fpsCounter);

	// ------- Player 1 ------- //
	//Display Game Object (owns text components for UI)
	auto qBertDisplay = std::make_shared<GameObject>();;
	qBertDisplay->SetPosition(30, 100);

	qBertDisplay->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(qBertDisplay.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	qBertDisplay->AddComponent<TextComponent>(std::make_shared<TextComponent>(qBertDisplay.get(), "Player 1 -- Buttons: A/B", qBertBigFont));
	auto healthTextComp = qBertDisplay->AddComponent<TextComponent>(std::make_shared<TextComponent>(qBertDisplay.get(), "Lives: 5", qBertSmallFont));
	healthTextComp->SetPosition(0, 30); //Servers a translation relative to the parent object
	auto scoreTextComp = qBertDisplay->AddComponent<TextComponent>(std::make_shared<TextComponent>(qBertDisplay.get(), "Score: 0", qBertSmallFont));
	scoreTextComp->SetPosition(0, 55); //Servers a translation relative to the parent object
	Add(qBertDisplay);

	//Observer -> link up the text components to display to (doesn't own two text components in this case)
	auto qBertHealthDisplay = std::make_shared<HealthDisplay>(healthTextComp);
	auto qBertScoreDisplay = std::make_shared<ScoreDisplay>(scoreTextComp);

	//Q-Bert itself, add components + add observer to components
	auto qBert = std::make_shared<GameObject>();

	int nbLives = 5;
	auto pHealth = qBert->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(qBert.get(), nbLives));
	pHealth->GetSubject()->AddObserver(qBertHealthDisplay);

	auto pChar = qBert->AddComponent<CharacterComponent>(std::make_shared<CharacterComponent>(qBert.get()));
	pChar->GetSubject()->AddObserver(qBertScoreDisplay);
	Add(qBert);

	// ------- Player 2 ------- //
	//Display Game Object (owns text components for UI)
	auto p2UI = std::make_shared<GameObject>();;
	p2UI->SetPosition(30, 250);

	p2UI->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(p2UI.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	p2UI->AddComponent<TextComponent>(std::make_shared<TextComponent>(p2UI.get(), "Player 2 -- Buttons: X/Y", qBertBigFont));
	auto p2HealthTextComp = p2UI->AddComponent<TextComponent>(std::make_shared<TextComponent>(p2UI.get(), "Lives: 5", qBertSmallFont));
	p2HealthTextComp->SetPosition(0, 30);
	auto p2ScoreTextComp = p2UI->AddComponent<TextComponent>(std::make_shared<TextComponent>(p2UI.get(), "Score: 0", qBertSmallFont));
	p2ScoreTextComp->SetPosition(0, 55);
	Add(p2UI);

	//Observer -> link up the text components to display to (doesn't own two text components in this case)
	auto p2HealthDisplay = std::make_shared<HealthDisplay>(p2HealthTextComp);
	auto p2ScoreDisplay = std::make_shared<ScoreDisplay>(p2ScoreTextComp);

	//Player itself, add components + add observer to components
	auto p2 = std::make_shared<GameObject>();

	auto pHealthP2 = p2->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(p2.get(), nbLives));
	pHealthP2->GetSubject()->AddObserver(p2HealthDisplay);

	auto pCharP2 = p2->AddComponent<CharacterComponent>(std::make_shared<CharacterComponent>(p2.get()));
	pCharP2->GetSubject()->AddObserver(p2ScoreDisplay);
	Add(p2);

	//Input
	input.AddInputAction((int)KeyboardButton::A, ControllerButton::ButtonA, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<ScoreCommand>(qBert.get()));
	input.AddInputAction((int)KeyboardButton::B, ControllerButton::ButtonB, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<DieCommand>(qBert.get()));

	input.AddInputAction((int)KeyboardButton::X, ControllerButton::ButtonX, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<ScoreCommand>(p2.get()));
	input.AddInputAction((int)KeyboardButton::Y, ControllerButton::ButtonY, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<DieCommand>(p2.get()));
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
