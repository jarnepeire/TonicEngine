#include "HexGrid.h"
#include "GameObject.h"
#include <ImageComponent.h>

HexGrid::HexGrid(dae::GameObject* parent, const std::string& hexImagePath, const std::string& hexImageVisittedPath, int gridSize, int hexWidth, int hexHeight)
	: Component(parent)
	, m_ImageComponent(std::make_shared<ImageComponent>(parent, hexImagePath))
	, m_ImageComponentVisitted(std::make_shared<ImageComponent>(parent, hexImageVisittedPath))
	, m_GridSize(gridSize)
	, m_Grid()
	, m_Top()
	, m_HexWidth(hexWidth)
	, m_HexHeight(hexHeight)
{
	int offsetPerRow = int(hexWidth / 2.f);
	int offsetPerCol = int(hexHeight / 4.f);

	int horSize = int(hexWidth / 2.f);
	int verSize = int(hexHeight / 2.f);

	for (int row = 0; row <= gridSize; row++)
	{
		for (int col = 0; col < gridSize - row; col++)
		{
			auto pos = m_Transform.GetPosition() + m_pGameObject->GetTransform().GetPosition();
			
			glm::vec2 hexPos;
			hexPos.x = pos.x + (col * hexWidth) + (row * offsetPerRow);
			hexPos.y = pos.y - (row * hexHeight) + (row * offsetPerCol);

			std::shared_ptr<HexComponent> hex{ std::make_shared<HexComponent>(parent, m_ImageComponent, m_ImageComponentVisitted, row, col, hexWidth, hexHeight, hexPos)};
			m_Grid.push_back(hex);
		}
	}

	m_Top = m_Grid.back();
}

void HexGrid::FixedUpdate(float dt)
{
	for (auto& hex : m_Grid)
	{
		hex->FixedUpdate(dt);
	}
}

void HexGrid::Update(float dt)
{
	for (auto& hex : m_Grid)
	{
		hex->Update(dt);
	}
}

void HexGrid::Render()
{
	for (auto& hex : m_Grid)
	{
		hex->Render();
	}
}

bool HexGrid::GetHexPosition(const HexCoordinate& hc, glm::vec2& hexPos) const
{
	for (auto& hex : m_Grid)
	{
		if (hex->GetHexCoordinate() == hc)
		{
			hexPos = hex->GetHexPosition();
			return true;
		}
	}
	return false;
}

void HexGrid::VisitHex(const HexCoordinate& hc)
{
	for (auto& hex : m_Grid)
	{
		if (hex->GetHexCoordinate() == hc)
		{
			hex->Visit();
		}
	}
}

bool HexGrid::IsHexVisited(const HexCoordinate& hc)
{
	for (auto& hex : m_Grid)
	{
		if (hex->GetHexCoordinate() == hc)
		{
			return hex->IsVisitted();
		}
	}
	return false;
}

//glm::vec2 HexGrid::GetHexPosition(const HexCoordinate& hc) const
//{
//	for (auto& hex : m_Grid)
//	{
//		if (hex->GetHexCoordinate() == hc)
//		{
//			return hex->GetHexPosition();
//		}
//	}
//	return glm::vec2(InvalidHexPosValue, InvalidHexPosValue);
//}
