#include "TonicEnginePCH.h"
#include "ImageComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Texture2D.h"

Tonic::ImageComponent::ImageComponent(const std::string& filename, float scale)
	: Component()
	, m_CanRender(true)
	, m_pTexture(ResourceManager::GetInstance().LoadTexture(filename))
	, m_ImageWidth()
	, m_ImageHeight()
	, m_Scale(scale)
{
}

void Tonic::ImageComponent::Initialize()
{
	//Calculate in the scale to the image width/height
	int w{}, h{};
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &w, &h);
	m_ImageWidth = w * m_Scale;
	m_ImageHeight = h * m_Scale;
}

void Tonic::ImageComponent::Render()
{
	if (m_CanRender && m_pTexture != nullptr)
	{
		auto pRender = m_pGameObject->GetComponent<RenderComponent>();
		const auto pos = m_Transform.GetPosition() + m_pGameObject->GetTransform().GetPosition();
		pRender->RenderTexture(*m_pTexture, pos.x, pos.y, m_Scale);
	}
}

void Tonic::ImageComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}
