#include "ControlsMenu.h"
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
ControlsMenu::ControlsMenu(const std::string& name, int idx)
	: dae::Scene(name, idx)
	, m_pToMainMenuButton()
	, m_ClickSoundID()
{
}

void ControlsMenu::Initialize()
{
	auto font48 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 48);
	auto font36 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto menuFont = ResourceManager::GetInstance().LoadFont("VCR_OSD_MONO.otf", 16);

	//Background
	auto bgObject = std::make_shared<GameObject>();
	bgObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(bgObject.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	bgObject->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(bgObject.get(), "QBert/ControlsMenuBackground.png"));

	auto pJumpUpComp = bgObject->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(bgObject.get(), "QBert/Tut_JumpUp_Spritesheet.png", 180, 155, 14, 100, 0.25f));
	pJumpUpComp->SetLocalPosition(480, 20);

	auto pJumpRightComp = bgObject->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(bgObject.get(), "QBert/Tut_JumpRight_Spritesheet.png", 180, 155, 14, 100, 0.25f));
	pJumpRightComp->SetLocalPosition(480, 140);

	auto pJumpDownComp = bgObject->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(bgObject.get(), "QBert/Tut_JumpDown_Spritesheet.png", 180, 155, 14, 100, 0.25f));
	pJumpDownComp->SetLocalPosition(480, 260);

	auto pJumpLeftComp = bgObject->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(bgObject.get(), "QBert/Tut_JumpLeft_Spritesheet.png", 180, 155, 14, 100, 0.25f));
	pJumpLeftComp->SetLocalPosition(480, 380);

	Add(bgObject);


	//Back to main menu button
	{
		auto playObj = std::make_shared<GameObject>();
		playObj->SetPosition(250, 425);

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

void ControlsMenu::FixedUpdate(float dt)
{
}

void ControlsMenu::Update(float dt)
{
	m_pToMainMenuButton->Update(dt);
	if (m_pToMainMenuButton->IsPressed() || m_Input.IsInputTriggered(ControllerButton::ButtonA, ControllerButtonType::wButton, dae::TriggerState::Released))
	{
		//Go to main menu
		m_pAudioSytem->Play(m_ClickSoundID, 0.5f);
		SceneManager::GetInstance().SetActiveScene("Menu");
	}
}

void ControlsMenu::Render() const
{
}