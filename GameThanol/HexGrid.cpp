#include "HexGrid.h"
#include "GameObject.h"
#include <ImageComponent.h>
#include "DiskComponent.h"
#include "SpriteComponent.h"
#include "HexComponent.h"

HexGrid::HexGrid(dae::GameObject* parent, int gridSize, int hexWidth, int hexHeight, int nbVisitsNeeded, const std::vector<std::string>& hexImagePaths, bool isAlternating)
	: Component(parent)
	, m_ImageComponents()
	, m_GridSize(gridSize)
	, m_Grid()
	, m_Top()
	, m_HexWidth(hexWidth)
	, m_HexHeight(hexHeight)
	, m_NbVisitsNeeded((isAlternating) ? 1 : nbVisitsNeeded)
	, m_IsAltering(isAlternating)
{
	for (int i = 0; i <= m_NbVisitsNeeded; ++i)
	{
		m_ImageComponents.push_back(std::make_shared<ImageComponent>(parent, hexImagePaths[i], 1.f));
	}
}

HexGrid::~HexGrid()
{
	m_Disks.clear();
}

void HexGrid::Initialize()
{
	int offsetPerRow = int(m_HexWidth / 2.f);
	int offsetPerCol = int(m_HexHeight / 4.f);

	int horSize = int(m_HexWidth / 2.f);
	int verSize = int(m_HexHeight / 2.f);

	for (int row = 0; row <= m_GridSize; row++)
	{
		for (int col = 0; col < m_GridSize - row; col++)
		{
			auto pos = m_Transform.GetPosition() + m_pGameObject->GetTransform().GetPosition();

			glm::vec2 hexPos;
			hexPos.x = pos.x + (col * m_HexWidth) + (row * offsetPerRow);
			hexPos.y = pos.y - (row * m_HexHeight) + (row * offsetPerCol);

			std::shared_ptr<HexComponent> hex{ std::make_shared<HexComponent>(m_pGameObject, m_ImageComponents, m_NbVisitsNeeded, row, col, m_HexWidth, m_HexHeight, hexPos) };
			hex->SetIsAlternating(m_IsAltering);
			m_Grid.push_back(hex);
		}
	}

	m_Top = m_Grid.back();
}

void HexGrid::PostInitialize()
{
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

const std::shared_ptr<HexComponent>& HexGrid::GetTop() const
{
	return m_Top;
}

std::shared_ptr<HexComponent> HexGrid::GetHexComponent(const HexCoordinate& hc)
{
	for (auto& hex : m_Grid)
	{
		if (hex->GetHexCoordinate() == hc)
		{
			return hex;
		}
	}
	return nullptr;
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

void HexGrid::UnvisitHex(const HexCoordinate& hc)
{
	for (auto& hex : m_Grid)
	{
		if (hex->GetHexCoordinate() == hc)
		{
			hex->Unvisit();
		}
	}
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

void HexGrid::AddDisk(DiskComponent* diskComp, const HexCoordinate& hc)
{
	auto pHex = GetHexComponent(hc);
	if (!pHex)
		return;

	glm::vec2 pos = pHex->GetHexPosition();
	if (hc.Col == 0) //Left side
	{
		pos.x = pos.x - (m_HexWidth / 2.f);
		pos.y = pos.y - (m_HexHeight / 2.f);
	}
	else //Right side
	{
		pos.x = pos.x + (m_HexWidth / 2.f);
		pos.y = pos.y - (m_HexHeight / 2.f);
	}

	pHex->SetNeighbouringDisk(diskComp);
	diskComp->GetParentObject()->SetPosition(pos.x, pos.y);
	diskComp->GetParentObject()->GetComponent<SpriteComponent>()->SetEnableRender(true);
	m_Disks.push_back(diskComp);
}

void HexGrid::RemoveDisk(DiskComponent* diskComp, const HexCoordinate& hc)
{
	auto pHex = GetHexComponent(hc);
	if (!pHex)
		return;

	auto itToRemove = std::remove_if(m_Disks.begin(), m_Disks.end(), [&diskComp](DiskComponent* disk)
		{
			return (disk == diskComp);
		});

	if (itToRemove != m_Disks.end())
	{
		diskComp->GetParentObject()->GetComponent<SpriteComponent>()->SetEnableRender(false);
		m_Disks.erase(itToRemove);
		pHex->SetNeighbouringDisk(nullptr);
	}
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
