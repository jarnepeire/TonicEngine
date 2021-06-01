#include "HexGrid.h"
#include "GameObject.h"
#include <ImageComponent.h>

HexGrid::HexGrid(dae::GameObject* parent, int gridSize, int hexWidth, int hexHeight, const std::vector<std::string>& hexImagePaths, bool isAlternating)
	: Component(parent)
	, m_ImageComponents()
	, m_GridSize(gridSize)
	, m_Grid()
	, m_Top()
	, m_HexWidth(hexWidth)
	, m_HexHeight(hexHeight)
{
	int nbVisitsNeeded = 1;
	for (int i = 0; i <= nbVisitsNeeded; ++i)
	{
		m_ImageComponents.push_back(std::make_shared<ImageComponent>(parent, hexImagePaths[i], 1.f));
	}
	InitializeGrid(gridSize, hexWidth, hexHeight, nbVisitsNeeded, isAlternating);
}

HexGrid::HexGrid(dae::GameObject* parent, int gridSize, int hexWidth, int hexHeight, int nbVisitsNeeded, const std::vector<std::string>& hexImagePaths, bool isAlternating)
	: Component(parent)
	, m_ImageComponents()
	, m_GridSize(gridSize)
	, m_Grid()
	, m_Top()
	, m_HexWidth(hexWidth)
	, m_HexHeight(hexHeight)
{
	for (int i = 0; i <= nbVisitsNeeded; ++i)
	{
		m_ImageComponents.push_back(std::make_shared<ImageComponent>(parent, hexImagePaths[i], 1.f));
	}
	InitializeGrid(gridSize, hexWidth, hexHeight, nbVisitsNeeded, isAlternating);
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

void HexGrid::ResetGrid()
{
	for (auto& hex : m_Grid)
	{
		hex->ResetVisit();
	}
}

bool HexGrid::IsGridCompleted() const
{
	for (auto& hex : m_Grid)
	{
		if (!hex->IsVisitted())
		{
			return false;
		}
	}
	return true;
}

void HexGrid::InitializeGrid(int gridSize, int hexWidth, int hexHeight, int nbVisitsNeeded, bool isAlternating)
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

			std::shared_ptr<HexComponent> hex{ std::make_shared<HexComponent>(m_pGameObject, m_ImageComponents, nbVisitsNeeded, row, col, hexWidth, hexHeight, hexPos) };
			hex->SetIsAlternating(isAlternating);
			m_Grid.push_back(hex);
		}
	}

	m_Top = m_Grid.back();
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
