#include "TonicEnginePCH.h"
#include "HealthDisplay.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "HealthComponent.h"

HealthDisplay::HealthDisplay(const std::shared_ptr<TextComponent>& pTextComponent)
	: m_pHealthText(pTextComponent)
{
}

HealthDisplay::HealthDisplay(const std::shared_ptr<TextComponent>& pTextComponent, float x, float y)
	: m_pHealthText(pTextComponent)
{
	m_pHealthText->SetPosition(x, y);
}

void HealthDisplay::Notify(dae::GameObject* object, Event e)
{
	if (e == Event::EVENT_PLAYER_LOST_LIFE)
	{
		auto health = object->GetComponent<HealthComponent>();
		if (health != nullptr)
		{
			m_pHealthText->SetText("Lives: " + std::to_string(health->GetNbLives()));
		}
	}
}