#include "EnemyObserver.h"
#include <GameObject.h>
#include "HexJumpAIComponent.h"
#include "HealthComponent.h"
#include "HexJumpComponent.h"
#include "SpriteComponent.h"

EnemyObserver::EnemyObserver(std::shared_ptr<dae::GameObject> qbertObject)
	: m_QBert(qbertObject)
{
}

void EnemyObserver::Notify(dae::GameObject* object, Event e)
{
	if (e == Event::EVENT_ENEMY_SPAWNED)
	{
		auto pHexJumpAI = object->GetComponent<HexJumpAIComponent>();
		if (pHexJumpAI)
			pHexJumpAI->StartWaiting();
	}
	else if (e == Event::EVENT_JUMPER_LANDED)
	{
		auto pHexJumpAI = object->GetComponent<HexJumpAIComponent>();
		if (pHexJumpAI)
			pHexJumpAI->StartWaiting();

		auto pSpriteComponent = object->GetComponent<SpriteComponent>();
		if (pSpriteComponent) pSpriteComponent->SetAnimationRow(0);
	}
	else if (e == Event::EVENT_JUMPER_FELL_OFF_GRID)
	{
		auto pHealth = object->GetComponent<HealthComponent>();
		if (pHealth)
		{
			pHealth->LoseLife();
			if (pHealth->HasDied())
			{
				auto pHexJumpAI = object->GetComponent<HexJumpAIComponent>();
				pHexJumpAI->SetActive(false);
			}
		}
	}
	else if (e == Event::EVENT_JUMPER_JUMPED)
	{
		auto pHexJump = object->GetComponent<HexJumpComponent>();
		if (pHexJump)
		{
			const auto& currCoord = pHexJump->GetCurrentCoordinate();
			const auto& jumpToCoord = pHexJump->GetJumpToCoordinate();
			bool jumpUp = ((jumpToCoord.Row - currCoord.Row) == 1);

			auto pSpriteComponent = object->GetComponent<SpriteComponent>();
			if (pSpriteComponent) pSpriteComponent->SetAnimationRow(1);
			if (jumpUp) //Mean's he jumped up
			{
				//Flip character
				bool jumpLeft = ((jumpToCoord.Col - currCoord.Col) == -1);
				if (pSpriteComponent) pSpriteComponent->SetIsLeft(jumpLeft);
			}
			else //Mean's he jumped down
			{
				//Flip character
				bool jumpLeft = ((jumpToCoord.Col - currCoord.Col) == 0);
				if (pSpriteComponent) pSpriteComponent->SetIsLeft(jumpLeft);
			}
		}
	}
}
