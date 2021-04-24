#include "TonicEnginePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>

void dae::SceneManager::InitializeScenegraph()
{
	for (auto& scene : m_Scenes)
	{
		scene->Initialize();
	}
}

void dae::SceneManager::FixedUpdate(float dt)
{
	m_Scenes[m_ActiveSceneIdx]->RootFixedUpdate(dt);
	m_Scenes[m_ActiveSceneIdx]->FixedUpdate(dt);
}

void dae::SceneManager::Update(float dt)
{
	m_Scenes[m_ActiveSceneIdx]->RootUpdate(dt);
	m_Scenes[m_ActiveSceneIdx]->Update(dt);
}

void dae::SceneManager::Render()
{
	m_Scenes[m_ActiveSceneIdx]->RootRender();
	m_Scenes[m_ActiveSceneIdx]->Render();
}

void dae::SceneManager::SetActiveScene(int index)
{
	if (size_t(index) < m_Scenes.size() && m_Scenes[index])
		m_ActiveSceneIdx = index;
	else if (index == -1)
		m_ActiveSceneIdx = (int)m_Scenes.size() - 1;
	else
		m_ActiveSceneIdx = 0;
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	std::vector<std::shared_ptr<Scene>>::iterator it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&name](std::shared_ptr<Scene>& pScene) { return (pScene->GetName() == name); });
	if (it == m_Scenes.end())
		return;

	std::shared_ptr<Scene> pScene = *it;
	m_ActiveSceneIdx = pScene->GetSceneIndex();
}

//void dae::SceneManager::AddScene(const std::shared_ptr<dae::Scene>& scene)
//{
//	m_ActiveSceneIdx = (int)m_Scenes.size();
//	m_Scenes.push_back(scene);
//}

void dae::SceneManager::AddGameScene(std::shared_ptr<Scene> scene)
{
	m_ActiveSceneIdx = (int)m_Scenes.size();
	m_Scenes.push_back(scene);
}

dae::Scene* dae::SceneManager::GetScene(const int index) const
{
	if (size_t(index) < m_Scenes.size() && m_Scenes[index])
		return m_Scenes[index].get();
	else
		return nullptr;
}

dae::Scene* dae::SceneManager::GetScene(const std::string& sceneTag) const
{
	std::vector<std::shared_ptr<Scene>>::const_iterator it = std::find_if(m_Scenes.begin(), m_Scenes.end(), 
		[&sceneTag](const std::shared_ptr<Scene>& pScene) 
		{
			return (pScene->GetName() == sceneTag); 
		});

	if (it == m_Scenes.end())
		return nullptr;
	else
		return (*it).get();
}

dae::Scene* dae::SceneManager::GetCurrentScene() const
{
	return m_Scenes[m_ActiveSceneIdx].get();
}
