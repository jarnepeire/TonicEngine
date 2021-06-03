#include "TonicEnginePCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

Scene::Scene(const std::string& name, int idx) 
	: m_Name(name) 
	, m_SceneIndex(idx)
	, m_Input()
	, m_pAudioSytem()
{}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	object->Initialize();
	object->PostInitialize();
	object->SetParentScene(this);

	m_Objects.push_back(object);
}

void dae::Scene::RootFixedUpdate(float dt)
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(dt);
	}
}

void dae::Scene::RootUpdate(float dt)
{
	for (auto& object : m_Objects)
	{
		object->Update(dt);
	}
}

void dae::Scene::RootRender()
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}
