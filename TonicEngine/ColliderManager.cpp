#include "TonicEnginePCH.h"
#include "ColliderManager.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Event.h"
#include "SpriteComponent.h"

using namespace dae;
dae::ColliderManager::ColliderManager()
	: m_Colliders(0)
{
}

void dae::ColliderManager::FixedUpdate(float)
{
	for (auto pCollider : m_Colliders)
	{
		auto pSprite = pCollider->GetParentObject()->GetComponent<SpriteComponent>();
		auto colliderPos = pCollider->GetWorldPosition();
		auto spritePos = pSprite->GetWorldPosition();
		
		if (pCollider->CanCheckForCollision())
		{
			for (auto pOtherCollider : m_Colliders)
			{
				if (pCollider == pOtherCollider)
					continue;

				bool collides = pCollider->CollideCheck(pOtherCollider);
				if (collides)
				{
					dae::GameObject* pCollidingObject = pOtherCollider->GetParentObject();
					pCollider->GetSubject()->Notify(pCollidingObject, Event::EVENT_OBJECT_COLLIDE);
				}
			}
		}
	}
}

void dae::ColliderManager::Update(float)
{
	
}

void dae::ColliderManager::AddCollider(ColliderComponent* pCollider)
{
	m_Colliders.push_back(pCollider);
}
