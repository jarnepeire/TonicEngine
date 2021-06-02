#pragma once
#include <Component.h>
#include <memory>
#include <string>
#include <vector>

namespace dae 
{
	class GameObject;
}
class ImageComponent;
class DiskComponent;

struct HexCoordinate
{
	HexCoordinate()
		: Row(0), Col(0) {}

	HexCoordinate(int r, int c)
		: Row(r), Col(c) {}

	HexCoordinate(const HexCoordinate& hc)
		: Row(hc.Row), Col(hc.Col) {}

	bool operator==(const HexCoordinate& hc) const
	{
		return (this->Row == hc.Row && this->Col == hc.Col);
	}

	int Row;
	int Col;
};

class HexComponent : public Component
{
public:

	HexComponent(dae::GameObject* parent, std::vector<std::shared_ptr<ImageComponent>> imageComps, int nbVisitsNeeded, int row, int col, int hexWidth, int hexHeight, const glm::vec2& pos);
	virtual ~HexComponent() = default;
	
	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	bool IsVisitted() const { return (m_Visits == m_NbVisitsNeeded); }
	void ResetVisit() { m_Visits = 0; }
	void Visit();

	const HexCoordinate& GetHexCoordinate() const { return m_HexCoordinate; }
	const glm::vec2& GetHexPosition() const { return m_Position; }

	void SetIsAlternating(bool b) { m_IsAlternating = b; }

	DiskComponent* GetNeighbouringDisk() { return m_NeighbouringDisk; }
	void SetNeighbouringDisk(DiskComponent* disk) { m_NeighbouringDisk = disk; }

private:
	std::vector<std::shared_ptr<ImageComponent>> m_ImageComponents;
	const int m_HexWidth, m_HexHeight;
	glm::vec2 m_Position;
	HexCoordinate m_HexCoordinate;
	int m_Visits;
	int m_NbVisitsNeeded;
	bool m_IsAlternating;
	DiskComponent* m_NeighbouringDisk;
};

