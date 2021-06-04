#include "GameOverMenu.h"
#include <GameObject.h>
#include <RenderComponent.h>
#include <TextComponent.h>
#include <Renderer.h>
#include <ResourceManager.h>
#include "MenuButton.h"
#include "ImageComponent.h"
#include <SDLAudio.h>
#include <LogAudio.h>
#include <AudioLocator.h>
#include <iostream>
#include <SpriteComponent.h>
#include "Colors.h"

using namespace dae;
GameOverMenu::GameOverMenu(const std::string& name, int idx)
	: dae::Scene(name, idx)
	, m_pToMainMenuButton()
	, m_pFinalScoreObj()
	, m_ClickSoundID()
{
}

void GameOverMenu::Initialize()
{
	auto font48 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 48);
	auto font36 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto menuFont = ResourceManager::GetInstance().LoadFont("VCR_OSD_MONO.otf", 16);

	//Background
	auto bgObject = std::make_shared<GameObject>();
	bgObject->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(bgObject.get(), "QBert/MenuBackground.png"));
	bgObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(bgObject.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	Add(bgObject);

	//UI Text
	auto pEndText = std::make_shared<GameObject>();;
	pEndText->SetPosition(30, 200);

	pEndText->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(pEndText.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	auto pTextComp = pEndText->AddComponent<TextComponent>(std::make_shared<TextComponent>(pEndText.get(), "You Lose!", font48));
	pTextComp->SetColor(Colors::COLOR_TABLE[ColorName::Red]);
	Add(pEndText);


	m_pFinalScoreObj = std::make_shared<GameObject>();
	m_pFinalScoreObj->SetPosition(30, 265);

	m_pFinalScoreObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(m_pFinalScoreObj.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	m_pFinalScoreObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(m_pFinalScoreObj.get(), "Final Score: 0", font36));
	Add(m_pFinalScoreObj);

	//Coily on block
	auto pCoily = std::make_shared<GameObject>();
	pCoily->SetPosition(450, 150);
	pCoily->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(pCoily.get(), dae::Renderer::GetInstance().GetSDLRenderer()));

	auto pCoilySpriteComp = pCoily->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(pCoily.get(), "QBert/Coily_Spritesheet.png", 16, 32, 1, 125, 2.5f));
	pCoilySpriteComp->SetAnimationRow(1);
	pCoilySpriteComp->SetIsLeft(true);

	Add(pCoily);


	//Back to main menu button
	{
		auto playObj = std::make_shared<GameObject>();
		playObj->SetPosition(250, 400);

		auto pButtonImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(playObj.get(), "QBert/ToMenuButton.png", 1.f));
		auto pButtonHoverImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(playObj.get(), "QBert/ToMenuButtonHover.png", 1.f));
		playObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(playObj.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
		auto pTextComp = playObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(playObj.get(), "(A)", menuFont));
		pTextComp->SetLocalPosition(85, 17.5f);
		pTextComp->SetColor(Colors::COLOR_TABLE[ColorName::DarkLimeGreen]);
		Add(playObj);

		m_pToMainMenuButton = std::make_shared<MenuButton>(pButtonImage, pButtonHoverImage);
	}

	//Sound
	SDLAudio* pSDLAudio = new SDLAudio();
	m_ClickSoundID = pSDLAudio->AddSound("../Data/Sounds/sfx_ClickSound.wav");

	m_pAudioSytem = std::make_shared<LogAudio>(pSDLAudio);
	AudioLocator::RegisterAudioSystem(m_pAudioSytem.get());
}

void GameOverMenu::FixedUpdate(float dt)
{
}

void GameOverMenu::Update(float dt)
{
	m_pToMainMenuButton->Update(dt);
	if (m_pToMainMenuButton->IsPressed() || m_Input.IsInputTriggered(ControllerButton::ButtonA, ControllerButtonType::wButton, dae::TriggerState::Released))
	{
		//Go to main menu
		m_pAudioSytem->Play(m_ClickSoundID, 0.5f);
		SceneManager::GetInstance().SetActiveScene("Menu");
	}
}

void GameOverMenu::Render() const
{
}

void GameOverMenu::SetFinalScore(int score)
{
	m_pFinalScoreObj->GetComponent<TextComponent>()->SetText("Final Score: " + std::to_string(score));
}
