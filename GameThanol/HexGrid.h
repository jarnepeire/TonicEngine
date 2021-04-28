#pragma once
#include "HexComponent.h"
#include <glm/vec2.hpp>

class HexGrid : public Component
{
public:
	HexGrid(dae::GameObject* parent, const std::string& hexImagePath, int gridSize, int hexWidth, int hexHeight);
	virtual ~HexGrid() = default;

	virtual void FixedUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void Render() override;

	const std::shared_ptr<HexComponent>& GetTop() const { return m_Top; }
	const glm::vec2& GetHexPosition(const HexCoordinate& hc) const;

private:
	std::shared_ptr<ImageComponent> m_ImageComponent;
	int m_GridSize;
	std::vector<std::shared_ptr<HexComponent>> m_Grid;
	std::shared_ptr<HexComponent> m_Top;
	
};

