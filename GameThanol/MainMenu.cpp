#include "MainMenu.h"
#include <InputManager.h>
#include <ResourceManager.h>

#include <GameObject.h>
#include <Scene.h>
#include <Renderer.h>
#include <KeyboardMapping.h>
#include <iostream>

//UI
#include "MenuButton.h"

//Sound
#include "AudioLocator.h"
#include "SDLAudio.h"
#include "LogAudio.h"

//Commands
#include "Command.h"
#include "ToSceneCommand.h"

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
#include <SpriteComponent.h>

using namespace dae;
MainMenu::MainMenu(const std::string& name, int idx)
	: Scene(name, idx)
	, m_pOnePlayerButton()
	, m_ClickSoundID()
{
}

void MainMenu::Initialize()
{
	
	auto qBertSmallFont = ResourceManager::GetInstance().LoadFont("CooperBlack.otf", 16);

	//Background
	auto bgObject = std::make_shared<GameObject>();
	bgObject->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(bgObject.get(), "QBert/MenuBackground.png"));
	bgObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(bgObject.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	Add(bgObject);

	//Qbert Logo
	auto logoObject = std::make_shared<GameObject>();
	logoObject->SetPosition(45, 30);
	logoObject->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(logoObject.get(), "QBert/QBertLogo.png", 0.25f));
	logoObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(logoObject.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	Add(logoObject);

	//Explanation texts
	//Text 1
	{
		auto textObj = std::make_shared<GameObject>();
		textObj->SetPosition(120, 85);

		textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(textObj.get(), "Jump on squares to ", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		auto pTextComp1 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(textObj.get(), "change them to", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp1->SetLocalPosition(0, 15);

		auto pTextComp2 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(textObj.get(), "the target color", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp2->SetLocalPosition(0, 30);

		textObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(textObj.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
		Add(textObj);
	}

	//Text 2
	{
		auto textObj = std::make_shared<GameObject>();
		textObj->SetPosition(140, 150);

		textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(textObj.get(), "Stay on playfield!", qBertSmallFont, SDL_Color{ 4, 179, 4 }));

		auto pTextComp1 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(textObj.get(), "jumping off results", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp1->SetLocalPosition(0, 15);

		auto pTextComp2 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(textObj.get(), "in a fatal plummet", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp2->SetLocalPosition(0, 30);

		auto pTextComp3 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(textObj.get(), "unless a disk is there", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp3->SetLocalPosition(0, 45);

		textObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(textObj.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
		Add(textObj);
	}

	//Text 3
	{
		auto textObj = std::make_shared<GameObject>();
		textObj->SetPosition(160, 230);

		textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(textObj.get(), "Avoid all objects", qBertSmallFont, SDL_Color{ 4, 179, 4 }));

		auto pTextComp1 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(textObj.get(), "and creatures that", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp1->SetLocalPosition(0, 15);

		auto pTextComp2 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(textObj.get(), "are not green", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp2->SetLocalPosition(0, 30);

		textObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(textObj.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
		Add(textObj);
	}

	//Text 4
	{
		auto textObj = std::make_shared<GameObject>();
		textObj->SetPosition(180, 300);

		textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(textObj.get(), "Use spinning disks", qBertSmallFont, SDL_Color{ 4, 179, 4 }));

		auto pTextComp1 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(textObj.get(), "to lure snake to", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp1->SetLocalPosition(0, 15);

		auto pTextComp2 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(textObj.get(), "his death", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp2->SetLocalPosition(0, 30);

		textObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(textObj.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
		Add(textObj);
	}

	//One player button
	{
		auto playObj = std::make_shared<GameObject>();
		playObj->SetPosition(50, 400);

		auto pButtonImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(playObj.get(), "QBert/OnePlayerButton.png", 1.f));
		auto pButtonHoverImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(playObj.get(), "QBert/OnePlayerButtonHover.png", 1.f));
		playObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(playObj.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
		Add(playObj);

		m_pOnePlayerButton = std::make_shared<MenuButton>(pButtonImage, pButtonHoverImage);
	}


	//Two player button
	{
		auto playObj = std::make_shared<GameObject>();
		playObj->SetPosition(200, 400);

		auto pButtonImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(playObj.get(), "QBert/TwoPlayerButton.png", 1.f));
		auto pButtonHoverImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(playObj.get(), "QBert/TwoPlayerButtonHover.png", 1.f));
		playObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(playObj.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
		Add(playObj);

		m_pTwoPlayerButton = std::make_shared<MenuButton>(pButtonImage, pButtonHoverImage);
	}

	//Versus button
	{
		auto playObj = std::make_shared<GameObject>();
		playObj->SetPosition(350, 400);

		auto pButtonImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(playObj.get(), "QBert/VersusButton.png", 1.f));
		auto pButtonHoverImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(playObj.get(), "QBert/VersusButtonHover.png", 1.f));
		playObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(playObj.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
		Add(playObj);

		m_pVersusButton = std::make_shared<MenuButton>(pButtonImage, pButtonHoverImage);
	}

	//Sound
	SDLAudio* pSDLAudio = new SDLAudio();
	m_ClickSoundID = pSDLAudio->AddSound("../Data/Sounds/sfx_ClickSound.wav");

	m_pAudioSytem = std::make_shared<LogAudio>(pSDLAudio);
	AudioLocator::RegisterAudioSystem(m_pAudioSytem.get());

	//Input
	m_Input.AddInputAction((int)KeyboardButton::F2, ControllerButton::NULL_VALUE, ControllerButtonType::NULL_VALUE, TriggerState::Pressed, std::make_shared<ToSceneCommand>("QBert"));

	//m_Input.AddInputAction((int)KeyboardButton::A, ControllerButton::ButtonA, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<ScoreCommand>(qBert.get(), scoreSoundId));
	//m_Input.AddInputAction((int)KeyboardButton::B, ControllerButton::ButtonB, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<DieCommand>(qBert.get(), diedSoundId));
	//
	//m_Input.AddInputAction((int)KeyboardButton::X, ControllerButton::ButtonX, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<ScoreCommand>(p2.get(), scoreSoundId));
	//m_Input.AddInputAction((int)KeyboardButton::Y, ControllerButton::ButtonY, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<DieCommand>(p2.get(), diedSoundId));
	



}

void MainMenu::FixedUpdate(float dt)
{
}

void MainMenu::Update(float dt)
{
	m_pOnePlayerButton->Update(dt);
	if (m_pOnePlayerButton->IsPressed())
	{
		//Go to level
		m_pAudioSytem->Play(m_ClickSoundID, 0.5f);
		SceneManager::GetInstance().SetActiveScene("QBert");
	}

	m_pTwoPlayerButton->Update(dt);
	if (m_pTwoPlayerButton->IsPressed())
	{
		//Go to level
		//...
		m_pAudioSytem->Play(m_ClickSoundID, 0.5f);
		std::cout << "Proceeding to level 1 TWO PLAYER...\n";
	}

	m_pVersusButton->Update(dt);
	if (m_pVersusButton->IsPressed())
	{
		//Go to level
		//...
		m_pAudioSytem->Play(m_ClickSoundID, 0.5f);
		std::cout << "Proceeding to level 1 VERSUS...\n";
	}
}

void MainMenu::Render() const
{
}

/*
	//Fonts
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);
	auto qBertBigFont = ResourceManager::GetInstance().LoadFont("CooperBlack.otf", 28);
	auto qBertSmallFont = ResourceManager::GetInstance().LoadFont("CooperBlack.otf", 22);

	//Background
	//auto bgObject = std::make_shared<GameObject>();
	//bgObject->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(bgObject.get(), "background.jpg"));
	//bgObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(bgObject.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	//Add(bgObject);

	//Logo
	//auto logoObject = std::make_shared<GameObject>();
	//logoObject->SetPosition(216, 180);
	//logoObject->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(logoObject.get(), "logo.png"));
	//logoObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(logoObject.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	//Add(logoObject);

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
	healthTextComp->SetLocalPosition(0, 30); //Servers a translation relative to the parent object
	auto scoreTextComp = qBertDisplay->AddComponent<TextComponent>(std::make_shared<TextComponent>(qBertDisplay.get(), "Score: 0", qBertSmallFont));
	scoreTextComp->SetLocalPosition(0, 55); //Servers a translation relative to the parent object
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
	p2HealthTextComp->SetLocalPosition(0, 30);
	auto p2ScoreTextComp = p2UI->AddComponent<TextComponent>(std::make_shared<TextComponent>(p2UI.get(), "Score: 0", qBertSmallFont));
	p2ScoreTextComp->SetLocalPosition(0, 55);
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

	//Audio system
	SDLAudio* pSDLAudio = new SDLAudio();
	unsigned int scoreSoundId = pSDLAudio->AddSound("../Data/Sounds/sfx_gain_score.wav");
	unsigned int diedSoundId = pSDLAudio->AddSound("../Data/Sounds/sfx_death.wav");

	m_pAudioSytem = std::make_shared<LogAudio>(pSDLAudio);
	AudioLocator::RegisterAudioSystem(m_pAudioSytem.get());

	//Input
	m_Input.AddInputAction((int)KeyboardButton::F2, ControllerButton::NULL_VALUE, ControllerButtonType::NULL_VALUE, TriggerState::Pressed, std::make_shared<ToSceneCommand>("QBert"));

	m_Input.AddInputAction((int)KeyboardButton::A, ControllerButton::ButtonA, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<ScoreCommand>(qBert.get(), scoreSoundId));
	m_Input.AddInputAction((int)KeyboardButton::B, ControllerButton::ButtonB, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<DieCommand>(qBert.get(), diedSoundId));

	m_Input.AddInputAction((int)KeyboardButton::X, ControllerButton::ButtonX, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<ScoreCommand>(p2.get(), scoreSoundId));
	m_Input.AddInputAction((int)KeyboardButton::Y, ControllerButton::ButtonY, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<DieCommand>(p2.get(), diedSoundId));


*/