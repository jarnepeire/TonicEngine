#include "TonicEnginePCH.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

FPSComponent::FPSComponent(dae::GameObject* parent, const std::shared_ptr<TextComponent>& pTextComp)
	: Component(parent)
	, m_DisplayFPS(true)
	, m_Frames()
	, m_TotalTime()
	, m_FPS()
	, m_pTextComponent(pTextComp)
{
}

FPSComponent::FPSComponent(dae::GameObject* parent, const std::shared_ptr<dae::Font>& font)
	: Component(parent)
	, m_DisplayFPS(true)
	, m_Frames()
	, m_TotalTime()
	, m_FPS()
{
	//To ensure there's a text component to receive the FPS stats
	m_pTextComponent = m_pGameObject->AddComponent<TextComponent>(std::make_shared<TextComponent>(parent, "0", font));
}

void FPSComponent::FixedUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void FPSComponent::Update(float dt)
{
	m_Frames++;
	m_TotalTime += dt;

	//We want to know how many frames passed per 1 seconds (hence the >= 1.f)
	if (m_TotalTime >= 1.f)
	{
		m_TotalTime -= 1.f;
		m_FPS = m_Frames;
		m_Frames = 0;

		//Update text
		if (m_DisplayFPS)
		{
			m_pTextComponent->SetText(std::to_string(m_FPS));
		}
	}
}

void FPSComponent::Render()
{
}
