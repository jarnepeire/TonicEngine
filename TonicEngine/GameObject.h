#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <vector>

class Component;

namespace dae
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:
		void Update(float dt) override;
		void Render() const override;
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		
		
		template<typename T>
		inline std::shared_ptr<T> GetComponent()
		{
			for (std::shared_ptr<Component> pComponent : m_pComponents)
			{
				auto pTemp = std::dynamic_pointer_cast<T>(pComponent);
				if (pTemp != nullptr)
					return pTemp;
			}
			return nullptr;
		}

		void AddComponent(std::shared_ptr<Component> component);
		Transform& GetTransform() { return m_Transform; }
		
	private:
		Transform m_Transform;
		std::vector<std::shared_ptr<Component>> m_pComponents;
	};

}
