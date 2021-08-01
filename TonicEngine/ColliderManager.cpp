#include "TonicEnginePCH.h"
#include "ColliderManager.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Event.h"
#include "Subject.h"

Tonic::ColliderManager::ColliderManager()
	: m_pColliders()
{
}

void Tonic::ColliderManager::Update(float)
{
	for (auto pCollider : m_pColliders)
	{
		if (pCollider->CanCheckForCollision())
		{
			for (auto pOtherCollider : m_pColliders)
			{
				//Don't check for self collision
				if (pCollider == pOtherCollider)
					continue;

				//Notify on collision with what object
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

void Tonic::ColliderManager::AddCollider(ColliderComponent* pCollider)
{
	m_pColliders.push_back(pCollider);
}
