#include "TonicEnginePCH.h"
#include "HealthDisplay.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "HealthComponent.h"
#include "GameEvent.h"

using namespace Tonic;
HealthDisplay::HealthDisplay(const std::shared_ptr<TextComponent>& pTextComponent)
	: m_pHealthText(pTextComponent)
{
}

HealthDisplay::HealthDisplay(const std::shared_ptr<TextComponent>& pTextComponent, float x, float y)
	: m_pHealthText(pTextComponent)
{
	m_pHealthText->SetLocalPosition(x, y);
}

void HealthDisplay::Notify(Tonic::GameObject* object, int eventId)
{
	if (eventId == (int)GameEvent::EVENT_CHARACTER_LOST_LIFE || eventId == (int)GameEvent::EVENT_LEVEL_RESET)
	{
		auto health = object->GetComponent<HealthComponent>();
		if (health != nullptr)
		{
			m_pHealthText->SetText("Lives: " + std::to_string(health->GetNbLives()));
		}
	}
}