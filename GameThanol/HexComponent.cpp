#include "HexComponent.h"
#include <ImageComponent.h>
#include <GameObject.h>
#include <glm/vec2.hpp>
#include <RenderComponent.h>
#include <MathHelper.h>

using namespace Tonic;
HexComponent::HexComponent(std::vector<std::shared_ptr<ImageComponent>> imageComps, int nbVisitsNeeded, int row, int col, int hexWidth, int hexHeight, const glm::vec2& pos)
	: Component()
	, m_ImageComponents(imageComps)
	, m_HexWidth(hexWidth)
	, m_HexHeight(hexHeight)
	, m_Position(pos)
	, m_HexCoordinate(row, col)
	, m_Visits(0)
	, m_NbVisitsNeeded(nbVisitsNeeded)
	, m_IsAlternating(false)
	, m_NeighbouringDisk(nullptr)
{
}

void HexComponent::Initialize()
{
}

void HexComponent::PostInitialize()
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
	auto pTexture = m_ImageComponents[m_Visits]->GetTexture();
	if (pTexture)
	{
		auto pRender = m_pGameObject->GetComponent<RenderComponent>();
		pRender->RenderTexture(*pTexture, m_Position.x, m_Position.y);
	}
}

void HexComponent::Unvisit()
{
	if (m_IsAlternating)
	{
		(IsVisitted()) ? --m_Visits : ++m_Visits;
	}
	else
	{
		Clamp<int>(--m_Visits, 0, m_NbVisitsNeeded);
	}
}

void HexComponent::Visit()
{
	if (m_IsAlternating)
	{
		(IsVisitted()) ? --m_Visits : ++m_Visits;
	}
	else
	{
		Clamp<int>(++m_Visits, 0, m_NbVisitsNeeded);
	}
}
