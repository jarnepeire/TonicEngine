#include "TonicEnginePCH.h"
#include "ScoreDisplay.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "CharacterComponent.h"

ScoreDisplay::ScoreDisplay(const std::shared_ptr<TextComponent>& pTextComponent)
	: m_pScoreText(pTextComponent)
{
}

ScoreDisplay::ScoreDisplay(const std::shared_ptr<TextComponent>& pTextComponent, float x, float y)
	: m_pScoreText(pTextComponent)
{
	m_pScoreText->SetLocalPosition(x, y);
}

void ScoreDisplay::Notify(dae::GameObject* object, Event e)
{
	if (e == Event::EVENT_PLAYER_SCORED)
	{
		auto character = object->GetComponent<CharacterComponent>();
		if (character != nullptr)
		{
			m_pScoreText->SetText("Score: " + std::to_string(character->GetScore()));
		}
	}
}