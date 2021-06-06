#include "SamSlickObserver.h"
#include <GameObject.h>
#include "HexGrid.h"
#include "HexJumpComponent.h"

SamSlickObserver::SamSlickObserver(std::shared_ptr<HexGrid> currentLevelGrid)
	: m_pGrid(currentLevelGrid)
{
}

void SamSlickObserver::Notify(dae::GameObject* object, Event e)
{
	if (e == Event::EVENT_JUMPER_LANDED)
	{
		auto pHexJump = object->GetComponent<HexJumpComponent>();
		const auto& hc = pHexJump->GetJumpToCoordinate();
		m_pGrid->UnvisitHex(hc);
	}
	else if (e == Event::EVENT_ENEMY_SPAWNED)
	{
		auto pHexJump = object->GetComponent<HexJumpComponent>();
		const auto& hc = pHexJump->GetCurrentCoordinate();
		m_pGrid->UnvisitHex(hc);
	}
}
