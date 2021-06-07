#include "TonicEnginePCH.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Scene.h"

Tonic::ColliderComponent::ColliderComponent(CollisionLayer collisionLayer, bool canCheckForCollision, float width, float height)
	: Component()
	, m_ColliderBox()
	, m_CollisionLayer(collisionLayer)
	, m_CanCheckForCollision(canCheckForCollision)
	, m_CanReceiveCheckForCollision(true)
	, m_Width(width)
	, m_Height(height)
{
}

void Tonic::ColliderComponent::PostInitialize()
{
	//Set location of collision box, taking into account the parent object's transform
	const auto& parentPos = m_pGameObject->GetTransform().GetPosition();
	const auto& compPos = m_Transform.GetPosition();
	m_ColliderBox.BottomLeft.x = (parentPos.x + compPos.x) - (m_Width / 2.f);
	m_ColliderBox.BottomLeft.y = (parentPos.y + compPos.y) + (m_Height / 2.f);

	m_ColliderBox.TopRight.x = (parentPos.x + compPos.x) + (m_Width / 2.f);
	m_ColliderBox.TopRight.y = (parentPos.y + compPos.y) - (m_Height / 2.f);

	//Add collider to the scene's collider manager to be updated
	m_pGameObject->GetParentScene()->AddColliderToScene(this);
}

void Tonic::ColliderComponent::Update(float)
{
	//Update location of collision box, taking into account the parent object's transform
	const auto& parentPos = m_pGameObject->GetTransform().GetPosition();
	const auto& compPos = m_Transform.GetPosition();
	m_ColliderBox.BottomLeft.x = (parentPos.x + compPos.x) - (m_Width / 2.f);
	m_ColliderBox.BottomLeft.y = (parentPos.y + compPos.y) + (m_Height / 2.f);

	m_ColliderBox.TopRight.x = (parentPos.x + compPos.x) + (m_Width / 2.f);
	m_ColliderBox.TopRight.y = (parentPos.y + compPos.y) - (m_Height / 2.f);
}

bool Tonic::ColliderComponent::CollideCheck(ColliderComponent* pCollider) const
{
	//Same layer means no collision
	if (m_CollisionLayer == pCollider->GetCollisionLayer())
		return false;

	//If cannot receive collision checks, return
	if (!pCollider->CanReceiveCheckForCollision())
		return false;

	const auto& otherColliderBox = pCollider->GetColliderBox();
	//Overlaps horizontally
	if (m_ColliderBox.BottomLeft.x < otherColliderBox.TopRight.x && m_ColliderBox.TopRight.x > otherColliderBox.BottomLeft.x)
	{
		//Overlaps vertically
		if (m_ColliderBox.BottomLeft.y > otherColliderBox.TopRight.y && m_ColliderBox.TopRight.y < otherColliderBox.BottomLeft.y)
		{
			return true;
		}	
	}
	return false;
}
