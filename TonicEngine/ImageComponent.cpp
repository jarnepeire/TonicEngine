#include "TonicEnginePCH.h"
#include "ImageComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "GameObject.h"

using namespace dae;
ImageComponent::ImageComponent(dae::GameObject* parent, const std::string& filename)
	: Component(parent)
	, m_Texture(ResourceManager::GetInstance().LoadTexture(filename))
{
}

void ImageComponent::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void ImageComponent::Render()
{
	if (m_Texture != nullptr)
	{
		auto pRender = m_pGameObject->GetComponent<RenderComponent>();
		const auto pos = m_Transform.GetPosition() + m_pGameObject->GetTransform().GetPosition();
		pRender->RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void ImageComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
