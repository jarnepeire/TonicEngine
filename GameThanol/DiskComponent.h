#pragma once
#include <Component.h>
#include "HexComponent.h"
#include <string>

class HexGrid;
class SpriteComponent;
struct HexCoordinate;

class DiskComponent : public Component, public std::enable_shared_from_this<DiskComponent>
{
public:
	DiskComponent(dae::GameObject* parent, float timeToMove);
	virtual ~DiskComponent() = default;

	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	void Move(dae::GameObject* pObjToMove, const glm::vec2& toPosition);
	void AttachToGrid(std::shared_ptr<HexGrid> hexGrid, const HexCoordinate& hc);
private:
	std::shared_ptr<HexGrid> m_Grid;
	bool m_CanMove;
	dae::GameObject* m_pObjectToMove;
	glm::vec2 m_StartPosition;
	glm::vec2 m_MoveToPosition;
	float m_Timer;
	float m_TimeToMove;
	HexCoordinate m_AttachedHexCoordinate;
};