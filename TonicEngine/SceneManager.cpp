#include "TonicEnginePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputLocator.h"
#include "AudioLocator.h"
#include "AudioSystem.h"
#include <algorithm>

void Tonic::SceneManager::InitializeScenegraph()
{
	for (auto& scene : m_Scenes)
	{
		scene->Initialize();
	}
}

void Tonic::SceneManager::FixedUpdate(float dt)
{
	m_Scenes[m_ActiveSceneIdx]->RootFixedUpdate(dt);
	m_Scenes[m_ActiveSceneIdx]->FixedUpdate(dt);
}

void Tonic::SceneManager::Update(float dt)
{
	m_Scenes[m_ActiveSceneIdx]->RootUpdate(dt);
	m_Scenes[m_ActiveSceneIdx]->Update(dt);
}

void Tonic::SceneManager::Render()
{
	m_Scenes[m_ActiveSceneIdx]->RootRender();
	m_Scenes[m_ActiveSceneIdx]->Render();
}

void Tonic::SceneManager::SetActiveScene(int index)
{
	if (size_t(index) < m_Scenes.size() && m_Scenes[index])
		m_ActiveSceneIdx = index;
	else if (index == -1)
		m_ActiveSceneIdx = (int)m_Scenes.size() - 1;
	else
		m_ActiveSceneIdx = 0;

	//Swap out input for new scene's input
	InputManager* pInput = &m_Scenes[m_ActiveSceneIdx]->GetInput();
	InputLocator::RegisterInputManager(pInput);

	//Swap out audio system for new scene's input
	Tonic::AudioSystem* pAudioSystem = m_Scenes[m_ActiveSceneIdx]->GetAudioSystem().get();
	AudioLocator::RegisterAudioSystem(pAudioSystem);
}

void Tonic::SceneManager::SetActiveScene(const std::string& name)
{
	std::vector<std::shared_ptr<Scene>>::iterator it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&name](std::shared_ptr<Scene>& pScene) { return (pScene->GetName() == name); });
	if (it == m_Scenes.end())
		return;

	std::shared_ptr<Scene> pScene = *it;
	m_ActiveSceneIdx = pScene->GetSceneIndex();

	//Swap out input for new scene's input
	InputManager* pInput = &m_Scenes[m_ActiveSceneIdx]->GetInput();
	InputLocator::RegisterInputManager(pInput);

	//Swap out audio system for new scene's input
	AudioSystem* pAudioSystem = m_Scenes[m_ActiveSceneIdx]->GetAudioSystem().get();
	AudioLocator::RegisterAudioSystem(pAudioSystem);
}

//void Tonic::SceneManager::AddScene(const std::shared_ptr<Tonic::Scene>& scene)
//{
//	m_ActiveSceneIdx = (int)m_Scenes.size();
//	m_Scenes.push_back(scene);
//}

void Tonic::SceneManager::AddGameScene(std::shared_ptr<Scene> scene)
{
	m_ActiveSceneIdx = (int)m_Scenes.size();
	m_Scenes.push_back(scene);
}

Tonic::Scene* Tonic::SceneManager::GetScene(const int index) const
{
	if (size_t(index) < m_Scenes.size() && m_Scenes[index])
		return m_Scenes[index].get();
	else
		return nullptr;
}

Tonic::Scene* Tonic::SceneManager::GetScene(const std::string& sceneTag) const
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

Tonic::Scene* Tonic::SceneManager::GetCurrentScene() const
{
	return m_Scenes[m_ActiveSceneIdx].get();
}
