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
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto pEndText = std::make_shared<GameObject>();;
	pEndText->SetPosition(30, 250);

	pEndText->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(pEndText.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	pEndText->AddComponent<TextComponent>(std::make_shared<TextComponent>(pEndText.get(), "Game Over!", font));
	Add(pEndText);


	m_pFinalScoreObj = std::make_shared<GameObject>();;
	m_pFinalScoreObj->SetPosition(30, 350);

	m_pFinalScoreObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(m_pFinalScoreObj.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	m_pFinalScoreObj->AddComponent<TextComponent>(std::make_shared<TextComponent>(m_pFinalScoreObj.get(), "Final Score: 0", font));
	Add(m_pFinalScoreObj);


	//Back to main menu button
	{
		auto playObj = std::make_shared<GameObject>();
		playObj->SetPosition(250, 400);

		auto pButtonImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(playObj.get(), "QBert/ToMenuButton.png", 1.f));
		auto pButtonHoverImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(playObj.get(), "QBert/ToMenuButtonHover.png", 1.f));
		playObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(playObj.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
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
	if (m_pToMainMenuButton->IsPressed())
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
