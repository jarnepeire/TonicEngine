#include "HexComponent.h"
#include <ImageComponent.h>
#include <GameObject.h>
#include <glm/vec2.hpp>
#include <RenderComponent.h>

using namespace dae;
HexComponent::HexComponent(dae::GameObject* parent, std::shared_ptr<ImageComponent> imageComp, int row, int col, int hexWidth, int hexHeight, const glm::vec2& pos)
	: Component(parent)
	, m_ImageComponent(imageComp)
	, m_HexWidth(hexWidth)
	, m_HexHeight(hexHeight)
	, m_Position(pos)
	, m_HexCoordinate(row, col)
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
	auto pTexture = m_ImageComponent->GetTexture();
	if (pTexture)
	{
		auto pRender = m_pGameObject->GetComponent<RenderComponent>();
		pRender->RenderTexture(*pTexture, m_Position.x, m_Position.y);
	}
}
