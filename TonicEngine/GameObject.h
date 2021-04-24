#pragma once
#include "Transform.h"
#include <vector>

class Component;
namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject & other) = delete;
		GameObject(GameObject && other) = delete;
		GameObject& operator=(const GameObject & other) = delete;
		GameObject& operator=(GameObject && other) = delete;


		void FixedUpdate(float dt);
		void Update(float dt);
		void Render() const;
		void SetPosition(float x, float y);

		Transform& GetTransform() { return m_Transform; }

		//Templated Component Code:
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

		template<typename T>
		std::shared_ptr<T> AddComponent(std::shared_ptr<Component> component)
		{
			m_pComponents.push_back(component);
			return std::dynamic_pointer_cast<T>(component);
		}
		
	private:
		Transform m_Transform;
		std::vector<std::shared_ptr<Component>> m_pComponents;
	};

}
