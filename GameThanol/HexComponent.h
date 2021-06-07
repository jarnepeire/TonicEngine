#pragma once
#include <Component.h>
#include <memory>
#include <string>
#include <vector>
#include "HexCoordinate.h"

namespace Tonic 
{
	class GameObject;
	class ImageComponent;
}
class DiskComponent;

class HexComponent : public Tonic::Component
{
public:

	HexComponent(Tonic::GameObject* parent, std::vector<std::shared_ptr<Tonic::ImageComponent>> imageComps, int nbVisitsNeeded, int row, int col, int hexWidth, int hexHeight, const glm::vec2& pos);
	virtual ~HexComponent() = default;
	
	void Initialize() override;
	void PostInitialize() override;
	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	bool IsVisitted() const { return (m_Visits == m_NbVisitsNeeded); }
	void ResetVisit() { m_Visits = 0; }
	void Unvisit();
	void Visit();

	const HexCoordinate& GetHexCoordinate() const { return m_HexCoordinate; }
	const glm::vec2& GetHexPosition() const { return m_Position; }

	void SetIsAlternating(bool b) { m_IsAlternating = b; }

	DiskComponent* GetNeighbouringDisk() { return m_NeighbouringDisk; }
	void SetNeighbouringDisk(DiskComponent* disk) { m_NeighbouringDisk = disk; }

private:
	std::vector<std::shared_ptr<Tonic::ImageComponent>> m_ImageComponents;
	const int m_HexWidth, m_HexHeight;
	glm::vec2 m_Position;
	HexCoordinate m_HexCoordinate;
	int m_Visits;
	int m_NbVisitsNeeded;
	bool m_IsAlternating;
	DiskComponent* m_NeighbouringDisk;
};

