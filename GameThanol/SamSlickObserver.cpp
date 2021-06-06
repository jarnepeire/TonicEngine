#include "SamSlickObserver.h"
#include <GameObject.h>
#include "HexGrid.h"
#include "HexJumpComponent.h"
#include <SpriteComponent.h>

SamSlickObserver::SamSlickObserver(std::shared_ptr<HexGrid> currentLevelGrid)
	: m_pGrid(currentLevelGrid)
{
}

void SamSlickObserver::Notify(dae::GameObject* object, Event e)
{
	if (e == Event::EVENT_JUMPER_LANDED)
	{
		//Pointer expired
		auto pGrid = m_pGrid.lock();
		if (!pGrid)
			return;

		auto pHexJump = object->GetComponent<HexJumpComponent>();
		const auto& hc = pHexJump->GetJumpToCoordinate();
		pGrid->UnvisitHex(hc);
	}
	else if (e == Event::EVENT_ENEMY_SPAWNED)
	{
		//Pointer expired
		auto pGrid = m_pGrid.lock();
		if (!pGrid)
			return;

		auto pHexJump = object->GetComponent<HexJumpComponent>();
		const auto& hc = pHexJump->GetCurrentCoordinate();
		pGrid->UnvisitHex(hc);
	}
	else if (e == Event::EVENT_ENEMY_FALLS)
	{
		auto pSprite = object->GetComponent<SpriteComponent>();
		pSprite->SetEnableRender(true);
	}
}
