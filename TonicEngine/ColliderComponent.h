#pragma once
#include "Component.h"
#include <memory>

namespace dae
{
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
	class ColliderComponent : public Component
	{
	public:
		ColliderComponent(dae::GameObject* parent, CollisionLayer collisionLayer, bool canCheckForCollision, float width, float height);
		virtual ~ColliderComponent() = default;

		void Initialize() override;
		void PostInitialize() override;
		void FixedUpdate(float) override {}
		void Update(float) override;
		void Render() override {}
		
		const CollisionLayer& GetCollisionLayer() const { return m_CollisionLayer; }
		const ColliderBox& GetColliderBox() const { return m_ColliderBox; }
		bool CollideCheck(ColliderComponent* pCollider);
		bool CanCheckForCollision() const { return m_CanCheckForCollision; }
		bool CanReceiveCheckForCollision() const { return m_CanReceiveCheckForCollision; }

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