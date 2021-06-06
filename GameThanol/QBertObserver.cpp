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

QBertObserver::QBertObserver(std::shared_ptr<HexGrid> currentLevelGrid)
	: m_pGrid(currentLevelGrid)
{
}

void QBertObserver::Notify(dae::GameObject* object, Event e)
{
	if (e == Event::EVENT_JUMPER_SAVED_BY_DISK)
	{
		//Object will be carried by disk
		//Disk needs to move a little bit above the top
		auto topPos = m_pGrid->GetTop()->GetHexPosition();
		topPos.y -= m_pGrid->GetHexHeight();

		//Get the hex associated with the disk
		const auto& prevHc = object->GetComponent<HexJumpComponent>()->GetPreviousCoordinate();
		auto pCurrentHex = m_pGrid->GetHexComponent(prevHc);
		if (pCurrentHex)
		{
			auto pDisk = pCurrentHex->GetNeighbouringDisk();
			if (pDisk)
				pDisk->Move(object, topPos);
		}
	}
	else if (e == Event::EVENT_JUMPER_LANDED)
	{
		auto pHexJump = object->GetComponent<HexJumpComponent>();
		const auto& hc = pHexJump->GetJumpToCoordinate();
		m_pGrid->VisitHex(hc);
	}
	else if (e == Event::EVENT_JUMPER_JUMPED)
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
				if (pSpriteComp) pSpriteComp->SetIsLeft(jumpLeft);
			}
			else //Mean's he jumped down
			{
				if (pSpriteComp) pSpriteComp->SetAnimationRow(0);

				//Flip character
				bool jumpLeft = ((jumpToCoord.Col - currCoord.Col) == 0);
				if (pSpriteComp) pSpriteComp->SetIsLeft(jumpLeft);
			}
		}
	}
	else if (e == Event::EVENT_JUMPER_FELL_OFF_GRID)
	{
		//Lose heath
		auto pHealth = object->GetComponent<HealthComponent>();
		if (pHealth)
			pHealth->LoseLife();

		//Reset anim
		auto pSpriteComp = object->GetComponent<SpriteComponent>();
		if (pSpriteComp) pSpriteComp->SetAnimationRow(0);
		if (pSpriteComp) pSpriteComp->SetIsLeft(false);
	}
	else if (e == Event::EVENT_PLAYER_DIED)
	{
		//Reset anim
		auto pSpriteComp = object->GetComponent<SpriteComponent>();
		if (pSpriteComp) pSpriteComp->SetAnimationRow(0);
		if (pSpriteComp) pSpriteComp->SetIsLeft(false);
	}
	else if (e == Event::EVENT_JUMPER_COLOR_CHANGE)
	{
		auto pCharacter = object->GetComponent<CharacterComponent>();
		if (pCharacter)
			pCharacter->GainScore((int)GameScore::SCORE_COLOR_CHANGE);
	}
}

