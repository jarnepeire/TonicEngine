#pragma once
#include "SceneManager.h"
#include "InputManager.h"
#include "ColliderManager.h"
#include <vector>
#include <memory>

namespace Tonic
{
	class AudioSystem;
	class ColliderComponent;
	class GameObject;

	class Scene
	{
	public:
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		virtual void Initialize() = 0;
		virtual void FixedUpdate(float dt) = 0;
		virtual void Update(float dt) = 0;
		virtual void Render() const = 0;

		/* Adds the object to the scene, and initializes the object and its components */
		void Add(const std::shared_ptr<GameObject>& object);

		/* Returns scene name */
		const std::string& GetName() const { return m_Name; }

		/* Returns scene index */
		const int GetSceneIndex() const { return m_SceneIndex; }

		/* Returns input manager of scene */
		InputManager& GetInput() { return m_Input; }

		/* Returns audio system of scene */
		const std::shared_ptr<AudioSystem>& GetAudioSystem() { return m_pAudioSytem; }

	protected:
		explicit Scene(const std::string& name);

		InputManager m_Input;
		ColliderManager m_ColliderManager;
		std::shared_ptr<AudioSystem> m_pAudioSytem;

	private: 
		friend class SceneManager;
		friend class ColliderComponent;

		/* Unique scene information */
		int m_SceneIndex;
		std::string m_Name;
		std::vector<std::shared_ptr<GameObject>> m_pObjects{};

		/* Private functions */
		void RootFixedUpdate(float deltaT);
		void RootUpdate(float deltaT);
		void RootRender();
		void AddColliderToScene(ColliderComponent* pCollider);
		void SetSceneIndex(int index);
	};

}
