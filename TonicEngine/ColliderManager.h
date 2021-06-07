#pragma once
#include <vector>
#include <memory>

namespace Tonic
{
	class ColliderComponent;
	class ColliderManager
	{
	public:
		ColliderManager();
		~ColliderManager() = default;

		void FixedUpdate(float dt);
		void Update(float dt);

		void AddCollider(ColliderComponent* pCollider);

	private:
		std::vector<ColliderComponent*> m_Colliders;
	};

}