#include "TonicEnginePCH.h"
#include "ScoreDisplay.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "CharacterComponent.h"
#include "GameEvent.h"

using namespace Tonic;
ScoreDisplay::ScoreDisplay(const std::shared_ptr<TextComponent>& pTextComponent)
	: m_pScoreText(pTextComponent)
{
}

ScoreDisplay::ScoreDisplay(const std::shared_ptr<TextComponent>& pTextComponent, float x, float y)
	: m_pScoreText(pTextComponent)
{
	m_pScoreText->SetLocalPosition(x, y);
}

void ScoreDisplay::Notify(Tonic::GameObject* object, int eventId)
{
	if (eventId == (int)GameEvent::EVENT_PLAYER_SCORED || eventId == (int)GameEvent::EVENT_LEVEL_RESET)
	{
		auto character = object->GetComponent<CharacterComponent>();
		if (character != nullptr)
		{
			m_pScoreText->SetText("Score: " + std::to_string(character->GetScore()));
		}
	}
}