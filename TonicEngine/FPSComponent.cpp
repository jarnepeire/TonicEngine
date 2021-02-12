#include "TonicEnginePCH.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

FPSComponent::FPSComponent(dae::GameObject* parent)
	: Component(parent)
	, m_DisplayFPS(false)
	, m_Frames()
	, m_TotalTime()
	, m_FPS()
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
	m_pGameObject->AddComponent(std::make_shared<TextComponent>(parent, "0", font));
}

void FPSComponent::Update(float dt)
{
	m_Frames++;
	m_TotalTime += dt;
	if (m_TotalTime >= 1.f)
	{
		m_TotalTime -= 1.f;
		m_FPS = m_Frames;
		m_Frames = 0;

		//Update text
		if (m_DisplayFPS)
		{
			m_pGameObject->GetComponent<TextComponent>()->SetText(std::to_string(m_FPS));
		}
	}
}

void FPSComponent::Render()
{
}
