#include "TonicEnginePCH.h"
#include "GameObject.h"
#include "Component.h"

Tonic::GameObject::GameObject()
	: m_pParentScene(nullptr)
	, m_Transform()
	, m_DepthValue(0.f)
	, m_pComponents()
{
}

void Tonic::GameObject::Initialize()
{
	for (auto pComp : m_pComponents)
	{
		pComp->Initialize();
	}
}

void Tonic::GameObject::PostInitialize()
{
	for (auto pComp : m_pComponents)
	{
		pComp->PostInitialize();
	}
}

void Tonic::GameObject::FixedUpdate(float dt)
{
	for (auto pComp : m_pComponents)
	{
		pComp->FixedUpdate(dt);
	}
}

void Tonic::GameObject::Update(float dt)
{
	for (auto pComp : m_pComponents)
	{
		pComp->Update(dt);
	}
}

void Tonic::GameObject::Render() const
{
	for (auto pComp : m_pComponents)
	{
		pComp->Render();
	}
}

void Tonic::GameObject::SetPosition(float x, float y, float z)
{
	m_Transform.SetPosition(x, y, z);
}
