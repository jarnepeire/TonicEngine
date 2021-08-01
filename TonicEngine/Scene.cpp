#include "TonicEnginePCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <algorithm>
#include "ColliderManager.h"

Tonic::Scene::Scene(const std::string& name)
	: m_SceneIndex(-1)
	, m_Name(name) 
	, m_Input()
	, m_ColliderManager()
	, m_pAudioSytem()
{}

Tonic::Scene::~Scene() = default;

void Tonic::Scene::Add(const std::shared_ptr<GameObject>& object)
{
	object->SetParentScene(this);
	object->Initialize();
	object->PostInitialize();

	m_pObjects.push_back(object);
}

void Tonic::Scene::RootFixedUpdate(float dt)
{
	m_ColliderManager.FixedUpdate(dt);
	for (auto& object : m_pObjects)
	{
		object->FixedUpdate(dt);
	}
}

void Tonic::Scene::RootUpdate(float dt)
{
	m_ColliderManager.Update(dt);
	for (auto& object : m_pObjects)
	{
		object->Update(dt);
	}
}

void Tonic::Scene::RootRender()
{
	//Sort objects on depth value (higher depth = further away)
	std::sort(m_pObjects.begin(), m_pObjects.end(), [](std::shared_ptr<Tonic::GameObject> pObjA, std::shared_ptr<Tonic::GameObject> pObjB)
		{
			return (pObjA->GetDepthValue() > pObjB->GetDepthValue());
		});

	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

void Tonic::Scene::AddColliderToScene(ColliderComponent* pCollider)
{
	m_ColliderManager.AddCollider(pCollider);
}

void Tonic::Scene::SetSceneIndex(int index)
{
	m_SceneIndex = index;
}
