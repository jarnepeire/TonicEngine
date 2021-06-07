#include "SamSlickObserver.h"
#include <GameObject.h>
#include "HexGrid.h"
#include "HexJumpComponent.h"
#include <SpriteComponent.h>
#include "ColliderComponent.h"
#include "GameEvent.h"

using namespace Tonic;
SamSlickObserver::SamSlickObserver(std::shared_ptr<HexGrid> currentLevelGrid)
	: m_pGrid(currentLevelGrid)
{
}

void SamSlickObserver::Notify(Tonic::GameObject* object, int eventId)
{
	if (eventId == (int)GameEvent::EVENT_JUMPER_LANDED)
	{
		//Pointer expired
		auto pGrid = m_pGrid.lock();
		if (!pGrid)
			return;

		auto pHexJump = object->GetComponent<HexJumpComponent>();
		const auto& hc = pHexJump->GetJumpToCoordinate();
		pGrid->UnvisitHex(hc);
	}
	else if (eventId == (int)GameEvent::EVENT_ENEMY_SPAWNED)
	{
		//Pointer expired
		auto pGrid = m_pGrid.lock();
		if (!pGrid)
			return;

		auto pHexJump = object->GetComponent<HexJumpComponent>();
		const auto& hc = pHexJump->GetCurrentCoordinate();
		pGrid->UnvisitHex(hc);
	}
	else if (eventId == (int)GameEvent::EVENT_ENEMY_FALLS)
	{
		auto pSprite = object->GetComponent<SpriteComponent>();
		pSprite->SetEnableRender(true);

		//Dont want to suddenly collide mid-air if we happen to fall on another object
		auto pCollider = object->GetComponent<Tonic::ColliderComponent>();
		if (pCollider)
			pCollider->SetCanReceiveCheckForCollision(false);
	}
}
