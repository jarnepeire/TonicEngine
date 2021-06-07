#pragma once
#include "Singleton.h"
#include <string>
#include <memory>
#include <vector>

namespace Tonic
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		/* Initializes all scenes, important to call this function after adding all scenes! */
		void InitializeScenegraph();
		void FixedUpdate(float dt);
		void Update(float dt);
		void Render();

		/* Sets the scene with the given index to the current scene that will be updated and rendered
			Sets the active scene to the first one on invalid index */
		void SetActiveScene(int index);

		/* Sets the scene with the given scene tag to the current scene that will be updated and rendered
			Sets the active scene to the first one on invalid scene tags */
		void SetActiveScene(const std::string& sceneTag);

		/* Adds a new scene to the manager and call its root- and initialize function */
		//void AddScene(const std::shared_ptr<Tonic::Scene>& scene);
		void AddGameScene(std::shared_ptr<Tonic::Scene> scene);

		/* Returns reference to vector of all scenes */
		std::vector<std::shared_ptr<Tonic::Scene>>& GetScenes() { return m_Scenes; }

		/* Returns pointer to the scene with the given index
		Returns nullptr on invalid index */
		Scene* GetScene(const int index) const;

		/* Returns pointer to the scene with the given scene tag
		Returns nullptr on invalid scene tag */
		Scene* GetScene(const std::string& sceneTag) const;

		/* Returns pointer to the scene that's currently active */
		Scene* GetCurrentScene() const;

		/* Returns the next free index value */
		int GetNextFreeIndex() const { return int(m_Scenes.size()); }

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		int m_ActiveSceneIdx = 0;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}