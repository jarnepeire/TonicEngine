#include "TonicEnginePCH.h"
#include "ImageComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Texture2D.h"

Tonic::ImageComponent::ImageComponent(Tonic::GameObject* parent, const std::string& filename, float scale)
	: Component(parent)
	, m_Texture(ResourceManager::GetInstance().LoadTexture(filename))
	, m_Scale(scale)
	, m_ImageWidth()
	, m_ImageHeight()
	, m_CanRender(true)
{
	//int w{}, h{};
	//SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &w, &h);
	//m_ImageWidth = w * scale;
	//m_ImageHeight = h * scale;
}

void Tonic::ImageComponent::Initialize()
{
	int w{}, h{};
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &w, &h);
	m_ImageWidth = w * m_Scale;
	m_ImageHeight = h * m_Scale;
}

void Tonic::ImageComponent::PostInitialize()
{
}

void Tonic::ImageComponent::FixedUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void Tonic::ImageComponent::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void Tonic::ImageComponent::Render()
{
	if (m_CanRender && m_Texture != nullptr)
	{
		auto pRender = m_pGameObject->GetComponent<RenderComponent>();
		const auto pos = m_Transform.GetPosition() + m_pGameObject->GetTransform().GetPosition();
		pRender->RenderTexture(*m_Texture, pos.x, pos.y, m_Scale);
	}
}

void Tonic::ImageComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
