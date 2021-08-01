#include "TonicEnginePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputLocator.h"
#include "AudioLocator.h"
#include "AudioSystem.h"
#include <algorithm>

void Tonic::SceneManager::InitializeScenegraph()
{
	for (auto& scene : m_pScenes)
	{
		scene->Initialize();
	}
}

void Tonic::SceneManager::FixedUpdate(float dt)
{
	m_pScenes[m_ActiveSceneIdx]->RootFixedUpdate(dt);
	m_pScenes[m_ActiveSceneIdx]->FixedUpdate(dt);
}

void Tonic::SceneManager::Update(float dt)
{
	m_pScenes[m_ActiveSceneIdx]->RootUpdate(dt);
	m_pScenes[m_ActiveSceneIdx]->Update(dt);
}

void Tonic::SceneManager::Render()
{
	m_pScenes[m_ActiveSceneIdx]->RootRender();
	m_pScenes[m_ActiveSceneIdx]->Render();
}

void Tonic::SceneManager::SetActiveScene(int index)
{
	InputManager* pOldInput = &m_pScenes[m_ActiveSceneIdx]->GetInput();

	if (size_t(index) < m_pScenes.size() && m_pScenes[index])
		m_ActiveSceneIdx = index;
	else if (index == -1)
		m_ActiveSceneIdx = (int)m_pScenes.size() - 1;
	else
		m_ActiveSceneIdx = 0;

	//Swap out input for new scene's input
	InputManager* pInput = &m_pScenes[m_ActiveSceneIdx]->GetInput();
	pInput->CarryOverInput(pOldInput);
	InputLocator::RegisterInputManager(pInput);

	//Swap out audio system for new scene's input
	Tonic::AudioSystem* pAudioSystem = m_pScenes[m_ActiveSceneIdx]->GetAudioSystem().get();
	AudioLocator::RegisterAudioSystem(pAudioSystem);
}

void Tonic::SceneManager::SetActiveScene(const std::string& name)
{
	std::vector<std::shared_ptr<Scene>>::iterator it = std::find_if(m_pScenes.begin(), m_pScenes.end(), [&name](std::shared_ptr<Scene>& pScene) { return (pScene->GetName() == name); });
	if (it == m_pScenes.end())
		return;

	InputManager* pOldInput = &m_pScenes[m_ActiveSceneIdx]->GetInput();

	std::shared_ptr<Scene> pScene = *it;
	m_ActiveSceneIdx = pScene->GetSceneIndex();

	//Swap out input for new scene's input
	InputManager* pInput = &m_pScenes[m_ActiveSceneIdx]->GetInput();
	pInput->CarryOverInput(pOldInput);
	InputLocator::RegisterInputManager(pInput);

	//Swap out audio system for new scene's input
	AudioSystem* pAudioSystem = m_pScenes[m_ActiveSceneIdx]->GetAudioSystem().get();
	AudioLocator::RegisterAudioSystem(pAudioSystem);
}

void Tonic::SceneManager::AddGameScene(const std::shared_ptr<Tonic::Scene>& scene)
{
	m_ActiveSceneIdx = (int)m_pScenes.size();
	m_pScenes.push_back(scene);
	scene->SetSceneIndex(m_ActiveSceneIdx);
}

Tonic::Scene* Tonic::SceneManager::GetScene(const int index) const
{
	if (size_t(index) < m_pScenes.size() && m_pScenes[index])
		return m_pScenes[index].get();
	else
		return nullptr;
}

Tonic::Scene* Tonic::SceneManager::GetScene(const std::string& sceneTag) const
{
	std::vector<std::shared_ptr<Scene>>::const_iterator it = std::find_if(m_pScenes.begin(), m_pScenes.end(), 
		[&sceneTag](const std::shared_ptr<Scene>& pScene) 
		{
			return (pScene->GetName() == sceneTag); 
		});

	if (it == m_pScenes.end())
		return nullptr;
	else
		return (*it).get();
}

Tonic::Scene* Tonic::SceneManager::GetCurrentScene() const
{
	return m_pScenes[m_ActiveSceneIdx].get();
}
