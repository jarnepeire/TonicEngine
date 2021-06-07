#pragma once
#include "Transform.h"
#include <vector>
#include <memory>
#include "Component.h"

namespace Tonic
{
	class Scene;
	class Texture2D;

	class GameObject final
	{
	public:
		GameObject();
		virtual ~GameObject() = default;

		GameObject(const GameObject & other) = delete;
		GameObject(GameObject && other) = delete;
		GameObject& operator=(const GameObject & other) = delete;
		GameObject& operator=(GameObject && other) = delete;

		/* Initializes the object and its components */
		void Initialize();

		/* Post initializes the object and its components 
			(we know with certainty all components have been initialized at this point) */
		void PostInitialize();

		/* Updates the game objects component at a fixed timestep */
		void FixedUpdate(float dt);

		/* Updates the game objects with the amount of time passed since previous frame */
		void Update(float dt);

		/* Renders all components that are applicable */
		void Render() const;
		
		/* Returns pointer to scene this object belongs to */
		Tonic::Scene* GetParentScene() { return m_pParentScene; }

		/* Returns reference to the transform of the game object */
		Tonic::Transform& GetTransform() { return m_Transform; }

		/* Returns depth value of this game object
			Used to determine what object gets rendered first */
		float GetDepthValue() const { return m_DepthValue; }

		/* Set depth value of this game object 
			Used to determine what object gets rendered first */
		void SetDepthValue(float depth) { m_DepthValue = depth; }
		
		/* Set position of transform of the game object */
		void SetPosition(float x, float y, float z = 0.f);

		/* Sets pointer to the scene this object belongs to */
		void SetParentScene(Tonic::Scene* pScene) { m_pParentScene = pScene; }

		/* Returns requested type 'T' of component if applicable
			Returns nullptr if not available */
		template<typename T>
		inline std::shared_ptr<T> GetComponent()
		{
			for (std::shared_ptr<Tonic::Component> pComponent : m_pComponents)
			{
				auto pTemp = std::dynamic_pointer_cast<T>(pComponent);
				if (pTemp != nullptr)
					return pTemp;
			}
			return nullptr;
		}

		/* Adds component of type 'T' and returns a shared pointer to the component */
		template<typename T>
		std::shared_ptr<T> AddComponent(std::shared_ptr<Tonic::Component> component)
		{
			m_pComponents.push_back(component);
			component->SetGameObject(this);
			return std::dynamic_pointer_cast<T>(component);
		}
		
	private:
		Tonic::Scene* m_pParentScene;
		Transform m_Transform;
		float m_DepthValue;
		std::vector<std::shared_ptr<Tonic::Component>> m_pComponents;
	};
}
