#include "TonicEnginePCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name, int idx) 
	: m_Name(name) 
	, m_SceneIndex(idx)
	, m_Input()
{}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
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
