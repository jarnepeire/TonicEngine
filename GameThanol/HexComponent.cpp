#include "HexComponent.h"
#include <ImageComponent.h>
#include <GameObject.h>
#include <glm/vec2.hpp>
#include <RenderComponent.h>

using namespace dae;
HexComponent::HexComponent(dae::GameObject* parent, std::shared_ptr<ImageComponent> imageComp, std::shared_ptr<ImageComponent> imageCompVisitted, int row, int col, int hexWidth, int hexHeight, const glm::vec2& pos)
	: Component(parent)
	, m_ImageComponent(imageComp)
	, m_ImageComponentVisitted(imageCompVisitted)
	, m_HexWidth(hexWidth)
	, m_HexHeight(hexHeight)
	, m_Position(pos)
	, m_HexCoordinate(row, col)
	, m_IsVisited(false)
{
}

void HexComponent::FixedUpdate(float)
{
}

void HexComponent::Update(float)
{
}

void HexComponent::Render()
{
	auto pTexture = (m_IsVisited) ? m_ImageComponentVisitted->GetTexture() : m_ImageComponent->GetTexture();
	if (pTexture)
	{
		auto pRender = m_pGameObject->GetComponent<RenderComponent>();
		pRender->RenderTexture(*pTexture, m_Position.x, m_Position.y);
	}
}
