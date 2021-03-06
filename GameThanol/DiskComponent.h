#pragma once
#include <Component.h>
#include "HexCoordinate.h"
#include <string>

class HexGrid;


class DiskComponent final : public Tonic::Component
{
public:
	DiskComponent(float timeToMove, std::shared_ptr<HexGrid> hexGrid, const HexCoordinate& hc);
	virtual ~DiskComponent() = default;

	void Initialize() override;
	void PostInitialize() override;
	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	void Move(Tonic::GameObject* pObjToMove, const glm::vec2& toPosition);
	void AttachToGrid(std::shared_ptr<HexGrid> hexGrid, const HexCoordinate& hc);
	void SetMovingSoundID(unsigned int id) { m_MovingSoundID = id; }
private:
	std::shared_ptr<HexGrid> m_Grid;
	bool m_CanMove;
	Tonic::GameObject* m_pObjectToMove;
	glm::vec2 m_StartPosition;
	glm::vec2 m_MoveToPosition;
	float m_Timer;
	float m_TimeToMove;
	HexCoordinate m_AttachedHexCoordinate;
	unsigned int m_MovingSoundID;
};