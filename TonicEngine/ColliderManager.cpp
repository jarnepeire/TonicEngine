#include "TonicEnginePCH.h"
#include "ColliderManager.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Event.h"
#include "SpriteComponent.h"

Tonic::ColliderManager::ColliderManager()
	: m_Colliders(0)
{
}

void Tonic::ColliderManager::FixedUpdate(float)
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
					Tonic::GameObject* pCollidingObject = pOtherCollider->GetParentObject();
					pCollider->GetSubject()->Notify(pCollidingObject, (int)Tonic::Event::EVENT_OBJECT_COLLIDE);
				}
			}
		}
	}
}

void Tonic::ColliderManager::Update(float)
{
	
}

void Tonic::ColliderManager::AddCollider(ColliderComponent* pCollider)
{
	m_Colliders.push_back(pCollider);
}
