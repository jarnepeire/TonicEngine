#pragma once
#include "Component.h"

namespace Tonic
{
	/* Rectangle help struct to define the collision boundaries */
	struct ColliderBox
	{
		ColliderBox() = default;
		ColliderBox(const glm::vec2& bottomLeft, const glm::vec2& topRight)
		{
			BottomLeft = bottomLeft;
			TopRight = topRight;
		}

		ColliderBox(float left, float bottom, float right, float top)
		{
			BottomLeft = glm::vec2(left, bottom);
			TopRight = glm::vec2(right, top);
		}

		glm::vec2 BottomLeft{};
		glm::vec2 TopRight{};
	};

	/* Collision layer (used to ignore colliders of the same layer) */
	enum class CollisionLayer
	{
		Layer0,
		Layer1,
		Layer2,
		Layer3,
		Layer4,
		Layer5,
		Layer6,
		Layer7,
		Layer8,
		Layer9,
	};

	class GameObject;
	class ColliderComponent final : public Component
	{
	public:
		ColliderComponent(CollisionLayer collisionLayer, bool canCheckForCollision, float width, float height);
		virtual ~ColliderComponent() = default;

		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		void Initialize() override {}
		void PostInitialize() override;
		void FixedUpdate(float) override {}
		void Update(float) override;
		void Render() override {}
		
		/* Returns collision layer */
		const CollisionLayer& GetCollisionLayer() const { return m_CollisionLayer; }
		
		/* Returns collider box struct, defining the colliders boundaries */
		const ColliderBox& GetColliderBox() const { return m_ColliderBox; }
		
		/* Returns the outcome of whether the given collider is overlapping with the current collider */
		bool CollideCheck(ColliderComponent* pCollider) const;

		/* Returns if this collider can check for other collisions */
		bool CanCheckForCollision() const { return m_CanCheckForCollision; }
		
		/* Returns if this collider can be checked by other colliders */
		bool CanReceiveCheckForCollision() const { return m_CanReceiveCheckForCollision; }

		/* Set value whether collider can be checked by other colliders */
		void SetCanReceiveCheckForCollision(bool b) { m_CanReceiveCheckForCollision = b; }
	
	private:
		ColliderBox m_ColliderBox;
		CollisionLayer m_CollisionLayer;
		bool m_CanCheckForCollision;
		bool m_CanReceiveCheckForCollision;
		float m_Width;
		float m_Height;
	};
}