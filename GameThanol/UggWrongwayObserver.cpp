#include "UggWrongwayObserver.h"
#include <GameObject.h>
#include "HexGrid.h"
#include "HexJumpComponent.h"
#include <SpriteComponent.h>
#include "ColliderComponent.h"

UggWrongwayObserver::UggWrongwayObserver(std::shared_ptr<HexGrid> currentLevelGrid)
	: m_pGrid(currentLevelGrid)
{
}

void UggWrongwayObserver::Notify(dae::GameObject* object, Event e)
{
	if (e == Event::EVENT_ENEMY_FALLS)
	{
		auto pSprite = object->GetComponent<SpriteComponent>();
		pSprite->SetEnableRender(true);

		//Dont want to suddenly collide mid-air if we happen to fall on another object
		auto pCollider = object->GetComponent<dae::ColliderComponent>();
		if (pCollider)
			pCollider->SetCanReceiveCheckForCollision(false);
	}
}
