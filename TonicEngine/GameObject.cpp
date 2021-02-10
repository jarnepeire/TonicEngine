#include "TonicEnginePCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextComponent.h"
#include "FPSComponent.h"

dae::GameObject::~GameObject()
{
}

void dae::GameObject::AddComponent(std::shared_ptr<Component> component)
{
	m_pComponents.push_back(component);
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

	if (m_Texture != nullptr)
	{
		const auto pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}

}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
