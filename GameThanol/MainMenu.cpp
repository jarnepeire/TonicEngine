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

//Components
#include <FPSComponent.h>
#include <TextComponent.h>
#include <RenderComponent.h>
#include <ImageComponent.h>
#include <SpriteComponent.h>
#include "QBertScene.h"
#include "Colors.h"

using namespace Tonic;
MainMenu::MainMenu(const std::string& name, int idx)
	: Scene(name, idx)
	, m_pOnePlayerButton()
	, m_ClickSoundID()
{
}

void MainMenu::Initialize()
{
	
	auto qBertSmallFont = ResourceManager::GetInstance().LoadFont("QBert/Fonts/CooperBlack.otf", 16);
	auto menuFont = ResourceManager::GetInstance().LoadFont("QBert/Fonts/VCR_OSD_MONO.otf", 16);

	//Background
	auto bgObject = std::make_shared<GameObject>();
	bgObject->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("QBert/Menu/MenuBackground.png"));
	bgObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
	Add(bgObject);

	//Qbert Logo
	auto logoObject = std::make_shared<GameObject>();
	logoObject->SetPosition(30, 30);
	logoObject->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("QBert/Menu/QBertLogo.png", 0.25f));
	logoObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
	Add(logoObject);

	//Qbert on disk
	auto qBertOnDisk = std::make_shared<GameObject>();
	qBertOnDisk->SetPosition(400, 150);
	qBertOnDisk->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
	
	auto pDiskSpriteComp = qBertOnDisk->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>("QBert/Props/Disk_Spritesheet.png", 16, 10, 4, 120, 4.f));
	pDiskSpriteComp->SetLocalPosition(30, 125);

	auto pQBertSpriteComp = qBertOnDisk->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>("QBert/Characters/QBert_Spritesheet.png", 37, 36, 8, 125, 2.5f));
	pQBertSpriteComp->SetIsFlipped(true);
	Add(qBertOnDisk);



	//Explanation texts
	//Text 1
	{
		auto textObj = std::make_shared<GameObject>();
		textObj->SetPosition(60, 100);

		textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("Jump on squares to ", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		auto pTextComp1 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("change them to", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp1->SetLocalPosition(0, 15);

		auto pTextComp2 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("the target color", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp2->SetLocalPosition(0, 30);

		textObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
		Add(textObj);
	}

	//Text 2
	{
		auto textObj = std::make_shared<GameObject>();
		textObj->SetPosition(80, 165);

		textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("Stay on playfield!", qBertSmallFont, SDL_Color{ 4, 179, 4 }));

		auto pTextComp1 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("jumping off results", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp1->SetLocalPosition(0, 15);

		auto pTextComp2 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("in a fatal plummet", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp2->SetLocalPosition(0, 30);

		auto pTextComp3 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("unless a disk is there", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp3->SetLocalPosition(0, 45);

		textObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
		Add(textObj);
	}

	//Text 3
	{
		auto textObj = std::make_shared<GameObject>();
		textObj->SetPosition(100, 245);

		textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("Avoid all objects", qBertSmallFont, SDL_Color{ 4, 179, 4 }));

		auto pTextComp1 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("and creatures that", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp1->SetLocalPosition(0, 15);

		auto pTextComp2 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("are not green", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp2->SetLocalPosition(0, 30);

		textObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
		Add(textObj);
	}

	//Text 4
	{
		auto textObj = std::make_shared<GameObject>();
		textObj->SetPosition(120, 315);

		textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("Use spinning disks", qBertSmallFont, SDL_Color{ 4, 179, 4 }));

		auto pTextComp1 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("to lure snake to", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp1->SetLocalPosition(0, 15);

		auto pTextComp2 = textObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("his death", qBertSmallFont, SDL_Color{ 4, 179, 4 }));
		pTextComp2->SetLocalPosition(0, 30);

		textObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
		Add(textObj);
	}

	//One player button
	{
		auto playObj = std::make_shared<GameObject>();
		playObj->SetPosition(30, 400);

		auto pButtonImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("QBert/Menu/OnePlayerButton.png", 1.f));
		auto pButtonHoverImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("QBert/Menu/OnePlayerButtonHover.png", 1.f));
		playObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
		auto pTextComp = playObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("(A)", menuFont));
		pTextComp->SetLocalPosition(85, 17.5f);
		pTextComp->SetColor(Colors::COLOR_TABLE[ColorName::DarkLimeGreen]);
		Add(playObj);

		m_pOnePlayerButton = std::make_shared<MenuButton>(pButtonImage, pButtonHoverImage);
	}

	//Two player button
	{
		auto playObj = std::make_shared<GameObject>();
		playObj->SetPosition(160, 400);

		auto pButtonImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("QBert/Menu/TwoPlayerButton.png", 1.f));
		auto pButtonHoverImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("QBert/Menu/TwoPlayerButtonHover.png", 1.f));
		playObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
		auto pTextComp = playObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("(B)", menuFont));
		pTextComp->SetLocalPosition(85, 17.5f);
		pTextComp->SetColor(Colors::COLOR_TABLE[ColorName::DarkLimeGreen]);
		Add(playObj);

		m_pTwoPlayerButton = std::make_shared<MenuButton>(pButtonImage, pButtonHoverImage);
	}

	//Versus button
	{
		auto playObj = std::make_shared<GameObject>();
		playObj->SetPosition(290, 400);

		auto pButtonImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("QBert/Menu/VersusButton.png", 1.f));
		auto pButtonHoverImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("QBert/Menu/VersusButtonHover.png", 1.f));
		playObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
		auto pTextComp = playObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("(X)", menuFont));
		pTextComp->SetLocalPosition(80, 17.5f);
		pTextComp->SetColor(Colors::COLOR_TABLE[ColorName::DarkLimeGreen]);
		Add(playObj);

		m_pVersusButton = std::make_shared<MenuButton>(pButtonImage, pButtonHoverImage);
	}

	//Controls button
	{
		auto playObj = std::make_shared<GameObject>();
		playObj->SetPosition(420, 400);

		auto pButtonImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("QBert/Menu/ControlsButton.png", 1.f));
		auto pButtonHoverImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("QBert/Menu/ControlsButtonHover.png", 1.f));
		playObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
		auto pTextComp = playObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("(Y)", menuFont));
		pTextComp->SetLocalPosition(85, 17.5f);
		pTextComp->SetColor(Colors::COLOR_TABLE[ColorName::DarkLimeGreen]);
		Add(playObj);

		m_pControlsButton = std::make_shared<MenuButton>(pButtonImage, pButtonHoverImage);
	}

	
	//Sound
	SDLAudio* pSDLAudio = new SDLAudio();
	m_ClickSoundID = pSDLAudio->AddSound("../Data/QBert/Sounds/sfx_ClickSound.wav");

	m_pAudioSytem = std::make_shared<LogAudio>(pSDLAudio);
	AudioLocator::RegisterAudioSystem(m_pAudioSytem.get());

	//Input
	m_Input.AddInputAction((int)KeyboardButton::F2, ControllerButton::NULL_VALUE, ControllerButtonType::NULL_VALUE, TriggerState::Pressed, std::make_shared<ToSceneCommand>("LevelOne"));

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
	if (m_pOnePlayerButton->IsPressed() || m_Input.IsInputTriggered(ControllerButton::ButtonA, ControllerButtonType::wButton, Tonic::TriggerState::Released))
	{
		//Go to level, reset to start over again
		m_pAudioSytem->Play(m_ClickSoundID, 0.5f);
		auto pScene = SceneManager::GetInstance().GetScene("LevelOne");
		auto pQBertScene = dynamic_cast<QBertScene*>(pScene);
		if (pQBertScene)
		{
			pQBertScene->ResetLevel();
			SceneManager::GetInstance().SetActiveScene("LevelOne");
		}
	
	}

	m_pTwoPlayerButton->Update(dt);
	if (m_pTwoPlayerButton->IsPressed() || m_Input.IsInputTriggered(ControllerButton::ButtonB, ControllerButtonType::wButton, Tonic::TriggerState::Released))
	{
		//Go to level as 2 players
		//Not implemented
		std::cout << "2 Player Mode not implemented yet!\n";
	}

	m_pVersusButton->Update(dt);
	if (m_pVersusButton->IsPressed() || m_Input.IsInputTriggered(ControllerButton::ButtonX, ControllerButtonType::wButton, Tonic::TriggerState::Released))
	{
		//Go to level as versus
		//Not implemented
		std::cout << "Versus Mode not implemented yet!\n";
	}

	m_pControlsButton->Update(dt);
	if (m_pControlsButton->IsPressed() || m_Input.IsInputTriggered(ControllerButton::ButtonY, ControllerButtonType::wButton, Tonic::TriggerState::Released))
	{
		//Go to controls menu
		m_pAudioSytem->Play(m_ClickSoundID, 0.5f);
		SceneManager::GetInstance().SetActiveScene("ControlsMenu");
	}
}

void MainMenu::Render() const
{
}