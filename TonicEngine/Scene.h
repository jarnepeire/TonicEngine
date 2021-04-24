#pragma once
#include "SceneManager.h"
#include <vector>
#include <memory>

namespace dae
{
	class GameObject;
	class Scene
	{
	public:
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		virtual void Initialize() = 0;
		virtual void FixedUpdate(float dt) = 0;
		virtual void Update(float dt) = 0;
		virtual void Render() const = 0;

		void Add(const std::shared_ptr<GameObject>& object);

		const std::string& GetName() const { return m_Name; }
		const int GetSceneIndex() const { return m_SceneIndex; }
	protected:
		explicit Scene(const std::string& name, int idx);



	private: 
		//friend Scene& SceneManager::CreateScene(const std::string& name);
		friend class SceneManager;

		/* Unique scene information */
		const int m_SceneIndex;
		std::string m_Name;

		std::vector<std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter; 

		/* Private functions */
		void RootFixedUpdate(float deltaT);
		void RootUpdate(float deltaT);
		void RootRender();
	};

}
