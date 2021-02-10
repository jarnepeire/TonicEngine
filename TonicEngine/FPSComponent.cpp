#include "TonicEnginePCH.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

FPSComponent::FPSComponent(dae::GameObject* parent, const std::shared_ptr<dae::Font>& font)
	: Component(parent)
	, m_DisplayFPS(true)
	, m_pTextComponent(std::make_shared<TextComponent>(m_pGameObject, "0", font))
	, m_Frames()
	, m_TotalTime()
	, m_FPS()
{
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
			m_pTextComponent->SetText(std::to_string(m_FPS));
			
		}
	}

	//Text
	m_pTextComponent->Update(dt);
}

void FPSComponent::Render()
{
	//Update text
	if (m_DisplayFPS)
	{
		m_pTextComponent->Render();
	}
}
