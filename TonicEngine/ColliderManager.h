#pragma once
#include <vector>
#include <memory>

namespace Tonic
{
	class ColliderComponent;
	class ColliderManager final
	{
	public:
		ColliderManager();
		~ColliderManager() = default;
		
		ColliderManager(const ColliderManager& other) = delete;
		ColliderManager(ColliderManager&& other) = delete;
		ColliderManager& operator=(const ColliderManager& other) = delete;
		ColliderManager& operator=(ColliderManager&& other) = delete;

		void FixedUpdate(float) {}
		void Update(float dt);

		/* Adds collider to be checked for collision */
		void AddCollider(ColliderComponent* pCollider);

	private:
		std::vector<ColliderComponent*> m_pColliders;
	};

}