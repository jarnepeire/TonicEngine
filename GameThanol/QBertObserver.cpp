#include "QBertObserver.h"
#include <GameObject.h>
#include "HealthComponent.h"
#include "HexGrid.h"
#include "HexJumpComponent.h"
#include "SpriteComponent.h"
#include "HexComponent.h"
#include "DiskComponent.h"
#include "CharacterComponent.h"
#include "GameScores.h"
#include <ColliderComponent.h>
#include "EnemyComponent.h"
#include "GameEvent.h"

using namespace Tonic;
QBertObserver::QBertObserver(std::shared_ptr<HexGrid> currentLevelGrid, std::shared_ptr<Tonic::GameObject> pQbertObj)
	: m_pGrid(currentLevelGrid)
	, m_pQBert(pQbertObj)
{
}

void QBertObserver::Notify(Tonic::GameObject* object, int eventId)
{
	if (eventId == (int)GameEvent::EVENT_JUMPER_SAVED_BY_DISK)
	{
		//Pointer expired
		auto pGrid = m_pGrid.lock();
		if (!pGrid)
			return;

		//Object will be carried by disk
		//Disk needs to move a little bit above the top
		auto topPos = pGrid->GetTop()->GetHexPosition();
		topPos.y -= pGrid->GetHexHeight();

		//Get the hex associated with the disk
		const auto& prevHc = object->GetComponent<HexJumpComponent>()->GetPreviousCoordinate();
		auto pCurrentHex = pGrid->GetHexComponent(prevHc);
		if (pCurrentHex)
		{
			auto pDisk = pCurrentHex->GetNeighbouringDisk();
			if (pDisk)
				pDisk->Move(object, topPos);
		}
	}
	else if (eventId == (int)GameEvent::EVENT_JUMPER_LANDED)
	{
		//Pointer expired
		auto pGrid = m_pGrid.lock();
		if (!pGrid)
			return;

		auto pHexJump = object->GetComponent<HexJumpComponent>();
		const auto& hc = pHexJump->GetJumpToCoordinate();
		pGrid->VisitHex(hc);
	}
	else if (eventId == (int)GameEvent::EVENT_JUMPER_JUMPED)
	{
		auto pSpriteComp = object->GetComponent<SpriteComponent>();
		auto pHexJump = object->GetComponent<HexJumpComponent>();
		if (pHexJump)
		{
			const auto& currCoord = pHexJump->GetCurrentCoordinate();
			const auto& jumpToCoord = pHexJump->GetJumpToCoordinate();
			bool jumpUp = ((jumpToCoord.Row - currCoord.Row) == 1);

			if (jumpUp) //Mean's he jumped up
			{
				if (pSpriteComp) pSpriteComp->SetAnimationRow(1);

				//Flip character
				bool jumpLeft = ((jumpToCoord.Col - currCoord.Col) == -1);
				if (pSpriteComp) pSpriteComp->SetIsFlipped(jumpLeft);
			}
			else //Mean's he jumped down
			{
				if (pSpriteComp) pSpriteComp->SetAnimationRow(0);

				//Flip character
				bool jumpLeft = ((jumpToCoord.Col - currCoord.Col) == 0);
				if (pSpriteComp) pSpriteComp->SetIsFlipped(jumpLeft);
			}
		}
	}
	else if (eventId == (int)GameEvent::EVENT_JUMPER_FELL_OFF_GRID)
	{
		//Respawn to top
		auto pHexJump = object->GetComponent<HexJumpComponent>();
		if (pHexJump)
			pHexJump->ResetToTop();

		//Lose heath
		auto pHealth = object->GetComponent<HealthComponent>();
		if (pHealth)
			pHealth->LoseLife();

		//Reset anim
		auto pSpriteComp = object->GetComponent<SpriteComponent>();
		if (pSpriteComp) pSpriteComp->SetAnimationRow(0);
		if (pSpriteComp) pSpriteComp->SetIsFlipped(false);
	}
	else if (eventId == (int)GameEvent::EVENT_CHARACTER_DIED)
	{
		//Reset anim
		auto pSpriteComp = object->GetComponent<SpriteComponent>();
		if (pSpriteComp) pSpriteComp->SetAnimationRow(0);
		if (pSpriteComp) pSpriteComp->SetIsFlipped(false);
	}
	else if (eventId == (int)GameEvent::EVENT_JUMPER_COLOR_CHANGE)
	{
		auto pCharacter = object->GetComponent<CharacterComponent>();
		if (pCharacter)
			pCharacter->GainScore((int)GameScore::SCORE_COLOR_CHANGE);
	}
	else if (eventId == (int)Tonic::Event::EVENT_OBJECT_COLLIDE)
	{
		auto pEnemyComponent = object->GetComponent<EnemyComponent>();
		if (!pEnemyComponent)
			return;
	
		//Expired Qbert pointer
		auto pQBert = m_pQBert.lock();
		if (!pQBert)
			return;

		auto pCharacter = pQBert->GetComponent<CharacterComponent>();
		EnemyType type = pEnemyComponent->GetEnemyType();
		if (type == EnemyType::SamSlick)
		{
			pCharacter->GainScore((int)GameScore::SCORE_CATCH_SAM_SLICK);
			object->GetComponent<HealthComponent>()->LoseLife();
		}
		else if (type == EnemyType::UggWrongway)
		{
			//Respawn to top
			auto pHexJump = pQBert->GetComponent<HexJumpComponent>();
			if (pHexJump)
				pHexJump->ResetToTop();

			//Lose life
			auto pHealth = pQBert->GetComponent<HealthComponent>();
			if (pHealth)
				pHealth->LoseLife();

			//Ugg or Wrongway loses life (and dissapears)
			object->GetComponent<HealthComponent>()->LoseLife();
		}
		else if (type == EnemyType::Coily)
		{
			//Respawn to top
			auto pHexJump = object->GetComponent<HexJumpComponent>();
			if (pHexJump)
				pHexJump->ResetToTop();

			//Lose life
			auto pHealth = pQBert->GetComponent<HealthComponent>();
			if (pHealth)
				pHealth->LoseLife();
		}
	}
}

