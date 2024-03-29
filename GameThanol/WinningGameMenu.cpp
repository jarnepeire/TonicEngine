//General
#include "WinningGameMenu.h"
#include <ResourceManager.h>
#include <Renderer.h>

//Components
#include <GameObject.h>
#include <RenderComponent.h>
#include <TextComponent.h>
#include <SpriteComponent.h>
#include <ImageComponent.h>

//Sound
#include <AudioLocator.h>
#include <SDLAudio.h>
#include <LogAudio.h>

//Project includes
#include "Colors.h"
#include "MenuButton.h"

using namespace Tonic;
WinningGameMenu::WinningGameMenu(const std::string& name)
	: Tonic::Scene(name)
	, m_pToMainMenuButton()
	, m_pFinalScoreObj()
	, m_ClickSoundID()
{
}

void WinningGameMenu::Initialize()
{
	auto font48 = ResourceManager::GetInstance().LoadFont("QBert/Fonts/Lingua.otf", 48);
	auto font36 = ResourceManager::GetInstance().LoadFont("QBert/Fonts/Lingua.otf", 36);
	auto menuFont = ResourceManager::GetInstance().LoadFont("QBert/Fonts/VCR_OSD_MONO.otf", 16);

	//Background
	auto bgObject = std::make_shared<GameObject>();
	bgObject->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("QBert/Menu/MenuBackground.png"));
	bgObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
	Add(bgObject);

	//UI Text
	auto pEndText = std::make_shared<GameObject>();;
	pEndText->SetPosition(30, 200);

	pEndText->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
	auto pTextComp = pEndText->AddComponent<TextComponent>(std::make_shared<TextComponent>("You Win!", font48));
	pTextComp->SetColor(Colors::COLOR_TABLE[ColorName::Green]);
	Add(pEndText);


	m_pFinalScoreObj = std::make_shared<GameObject>();
	m_pFinalScoreObj->SetPosition(30, 265);

	m_pFinalScoreObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
	m_pFinalScoreObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("Final Score: 0", font36));
	Add(m_pFinalScoreObj);


	//QBert on block
	auto qBertOnBlock = std::make_shared<GameObject>();
	qBertOnBlock->SetPosition(450, 150);
	qBertOnBlock->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));

	auto pBlockComp = qBertOnBlock->AddComponent<ImageComponent>(std::make_shared<ImageComponent>("QBert/Props/BlockGreen.png", 2.f));
	pBlockComp->SetLocalPosition(-5, 55);

	auto pQBertSpriteComp = qBertOnBlock->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>("QBert/Characters/QBert_Spritesheet.png", 37, 36, 8, 125, 1.5f));

	Add(qBertOnBlock);

	//Back to main menu button
	{
		auto playObj = std::make_shared<GameObject>();
		playObj->SetPosition(260, 400);

		auto pButtonImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>( "QBert/Menu/ToMenuButton.png", 1.f));
		auto pButtonHoverImage = playObj->AddComponent<ImageComponent>(std::make_shared<ImageComponent>( "QBert/Menu/ToMenuButtonHover.png", 1.f));
		playObj->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(Tonic::Renderer::GetInstance().GetSDLRenderer()));
		auto pTextComp2 = playObj->AddComponent<TextComponent>(std::make_shared<TextComponent>("(A)", menuFont));
		pTextComp2->SetLocalPosition(85, 17.5f);
		pTextComp2->SetColor(Colors::COLOR_TABLE[ColorName::DarkLimeGreen]);
		Add(playObj);

		m_pToMainMenuButton = std::make_shared<MenuButton>(pButtonImage, pButtonHoverImage);
	}

	//Sound
	SDLAudio* pSDLAudio = new SDLAudio();
	m_ClickSoundID = pSDLAudio->AddSound("../Data/QBert/Sounds/sfx_ClickSound.wav");

	m_pAudioSytem = std::make_shared<LogAudio>(pSDLAudio);
	AudioLocator::RegisterAudioSystem(m_pAudioSytem.get());
}

void WinningGameMenu::FixedUpdate(float)
{
}

void WinningGameMenu::Update(float dt)
{
	m_pToMainMenuButton->Update(dt);
	if (m_pToMainMenuButton->IsPressed() || m_Input.IsInputTriggered(ControllerButton::ButtonA, ControllerButtonType::wButton, Tonic::TriggerState::Released))
	{
		//Go to main menu
		m_pAudioSytem->Play(m_ClickSoundID, 0.5f);
		SceneManager::GetInstance().SetActiveScene("Menu");
	}
}

void WinningGameMenu::Render() const
{
}

void WinningGameMenu::SetFinalScore(int score)
{
	m_pFinalScoreObj->GetComponent<TextComponent>()->SetText("Final Score: " + std::to_string(score));
}
