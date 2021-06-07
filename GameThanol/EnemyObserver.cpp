#include "EnemyObserver.h"
#include <GameObject.h>
#include "HexJumpAIComponent.h"
#include "HealthComponent.h"
#include "HexJumpComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "EnemyComponent.h"

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

		auto pCollider = object->GetComponent<dae::ColliderComponent>();
		if (pCollider) 
			pCollider->SetCanReceiveCheckForCollision(true);
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
	else if (e == Event::EVENT_JUMPER_SAVED_BY_DISK)
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
	else if (e == Event::EVENT_CHARACTER_DIED)
	{
		auto pHexJumpAI = object->GetComponent<HexJumpAIComponent>();
		pHexJumpAI->SetActive(false);

		auto pSpriteComp = object->GetComponent<SpriteComponent>();
		pSpriteComp->SetEnableRender(false);

		auto pCollider = object->GetComponent<dae::ColliderComponent>();
		if (pCollider) 
			pCollider->SetCanReceiveCheckForCollision(false);

		auto pEnemyComp = object->GetComponent<EnemyComponent>();
		if (pEnemyComp)
			pEnemyComp->Kill();

	}
	else if (e == Event::EVENT_JUMPER_JUMPED)
	{
		auto pHexJump = object->GetComponent<HexJumpComponent>();
		if (pHexJump)
		{
			auto pSpriteComponent = object->GetComponent<SpriteComponent>();
			if (pSpriteComponent) pSpriteComponent->SetAnimationRow(1);


			//Check for left
			auto pEnemyComp = object->GetComponent<EnemyComponent>();
			auto enemyType = pEnemyComp->GetEnemyType();
			if (enemyType == EnemyType::SamSlick)
			{
				const auto& currCoord = pHexJump->GetCurrentCoordinate();
				const auto& jumpToCoord = pHexJump->GetJumpToCoordinate();
				bool jumpUp = ((jumpToCoord.Row - currCoord.Row) == 1);

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
			else if (enemyType == EnemyType::UggWrongway)
			{
				if (pSpriteComponent) pSpriteComponent->SetIsLeft(true);
			}

		}
	}
}
