#include "UggWrongwayObserver.h"
#include <GameObject.h>
#include "HexGrid.h"
#include "HexJumpComponent.h"
#include <SpriteComponent.h>
#include "ColliderComponent.h"
#include "GameEvent.h"

using namespace Tonic;
UggWrongwayObserver::UggWrongwayObserver(std::shared_ptr<HexGrid> currentLevelGrid)
	: m_pGrid(currentLevelGrid)
{
}

void UggWrongwayObserver::Notify(Tonic::GameObject* object, int eventId)
{
	if (eventId == (int)GameEvent::EVENT_ENEMY_FALLS)
	{
		auto pSprite = object->GetComponent<SpriteComponent>();
		pSprite->SetEnableRender(true);

		//Dont want to suddenly collide mid-air if we happen to fall on another object
		auto pCollider = object->GetComponent<Tonic::ColliderComponent>();
		if (pCollider)
			pCollider->SetCanReceiveCheckForCollision(false);
	}
}
