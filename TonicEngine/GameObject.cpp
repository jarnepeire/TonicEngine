#include "TonicEnginePCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "Subject.h"

dae::GameObject::~GameObject()
{
}

void dae::GameObject::Initialize()
{
	for (auto pComp : m_pComponents)
	{
		pComp->Initialize();
	}
}

void dae::GameObject::PostInitialize()
{
	for (auto pComp : m_pComponents)
	{
		pComp->PostInitialize();
	}
}

void dae::GameObject::FixedUpdate(float dt)
{
	for (auto pComp : m_pComponents)
	{
		pComp->FixedUpdate(dt);
	}
}

void dae::GameObject::Update(float dt)
{
	for (auto pComp : m_pComponents)
	{
		pComp->Update(dt);
	}
}

void dae::GameObject::Render() const
{
	for (auto pComp : m_pComponents)
	{
		pComp->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y, float z)
{
	m_Transform.SetPosition(x, y, z);
}
