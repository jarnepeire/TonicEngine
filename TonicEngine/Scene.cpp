#include "TonicEnginePCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <algorithm>
#include "ColliderManager.h"

using namespace dae;

Scene::Scene(const std::string& name, int idx) 
	: m_Name(name) 
	, m_SceneIndex(idx)
	, m_Input()
	, m_ColliderManager()
	, m_pAudioSytem()
{}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	object->SetParentScene(this);

	object->Initialize();
	object->PostInitialize();

	m_Objects.push_back(object);
}

void dae::Scene::RootFixedUpdate(float dt)
{
	m_ColliderManager.FixedUpdate(dt);
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(dt);
	}
}

void dae::Scene::RootUpdate(float dt)
{
	m_ColliderManager.Update(dt);
	for (auto& object : m_Objects)
	{
		object->Update(dt);
	}
}

void dae::Scene::RootRender()
{
	//Sort objects on depth value (higher depth = further away)
	std::sort(m_Objects.begin(), m_Objects.end(), [](std::shared_ptr<dae::GameObject> pObjA, std::shared_ptr<dae::GameObject> pObjB)
		{
			return (pObjA->GetDepthValue() > pObjB->GetDepthValue());
		});

	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void dae::Scene::AddColliderToScene(ColliderComponent* pCollider)
{
	m_ColliderManager.AddCollider(pCollider);
}
