#pragma once
#include "Component.h"
#include "HexCoordinate.h"
#include <glm/vec2.hpp>
#include <vector>
#include <string>

namespace Tonic
{
	class GameObject;
	class ImageComponent;
}

class DiskComponent;
class HexComponent;

class HexGrid : public Tonic::Component
{
public:
	HexGrid(Tonic::GameObject* parent, int gridSize, int hexWidth, int hexHeight, int nbVisitsNeeded, const std::vector<std::string>& hexImagePaths, bool isAlternating = false);
	virtual ~HexGrid();

	void Initialize() override;
	void PostInitialize() override;
	virtual void FixedUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void Render() override;

	const std::shared_ptr<HexComponent>& GetTop() const;
	std::shared_ptr<HexComponent> GetHexComponent(const HexCoordinate& hc);

	bool GetHexPosition(const HexCoordinate& hc, glm::vec2& hexPos) const;
	void UnvisitHex(const HexCoordinate& hc);
	void VisitHex(const HexCoordinate& hc);
	int GetHexWidth() const { return m_HexWidth; }
	int GetHexHeight() const { return m_HexHeight; }

	bool IsHexVisited(const HexCoordinate& hc);
	
	void ResetGrid();
	bool IsGridCompleted() const;

	void AddDisk(DiskComponent* diskComp, const HexCoordinate& hc);
	void RemoveDisk(DiskComponent* diskComp, const HexCoordinate& hc);
	int GetRemainingDiskAmount() const { return (int)m_Disks.size(); }

private:
	std::vector<std::shared_ptr<Tonic::ImageComponent>> m_ImageComponents;
	int m_GridSize;
	std::vector<std::shared_ptr<HexComponent>> m_Grid;
	std::shared_ptr<HexComponent> m_Top;
	std::vector<DiskComponent*> m_Disks;

	int m_HexWidth;
	int m_HexHeight;
	int m_NbVisitsNeeded;
	bool m_IsAltering;

	void InitializeGrid(int gridSize, int hexWidth, int hexHeight, int nbVisitsNeeded, bool isAlternating);
};

