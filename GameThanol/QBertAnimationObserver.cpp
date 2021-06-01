#include "QBertAnimationObserver.h"
#include <GameObject.h>
#include "HexJumpComponent.h"
#include <SpriteComponent.h>

QBertAnimationObserver::QBertAnimationObserver(std::shared_ptr<SpriteComponent> spriteComponent)
	: m_SpriteComponent(spriteComponent)
{
}

void QBertAnimationObserver::Notify(dae::GameObject* object, Event e)
{
	if (e == Event::EVENT_PLAYER_JUMPED)
	{
		auto pHexJump = object->GetComponent<HexJumpComponent>();
		if (pHexJump)
		{
			const auto& currCoord = pHexJump->GetCurrentCoordinate();
			const auto& jumpToCoord = pHexJump->GetJumpToCoordinate();
			bool jumpUp = ((jumpToCoord.Row - currCoord.Row) == 1);
			
			if (jumpUp) //Mean's he jumped up
			{
				m_SpriteComponent->SetAnimationRow(1);

				//Flip character
				bool jumpLeft = ((jumpToCoord.Col - currCoord.Col) == -1);
				m_SpriteComponent->SetIsLeft(jumpLeft);
			}
			else //Mean's he jumped down
			{
				m_SpriteComponent->SetAnimationRow(0);

				//Flip character
				bool jumpLeft = ((jumpToCoord.Col - currCoord.Col) == 0);
				m_SpriteComponent->SetIsLeft(jumpLeft);
			}
		}
	}
	else if (e == Event::EVENT_PLAYER_LOST_LIFE || e == Event::EVENT_PLAYER_DIED)
	{
		//Reset anim
		m_SpriteComponent->SetAnimationRow(0);
		m_SpriteComponent->SetIsLeft(false);
	}
}
