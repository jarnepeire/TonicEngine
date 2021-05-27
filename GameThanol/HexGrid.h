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
	bool GetHexPosition(const HexCoordinate& hc, glm::vec2& hexPos) const;
	int GetHexWidth() const { return m_HexWidth; }
	int GetHexHeight() const { return m_HexHeight; }

	
private:
	std::shared_ptr<ImageComponent> m_ImageComponent;
	int m_GridSize;
	std::vector<std::shared_ptr<HexComponent>> m_Grid;
	std::shared_ptr<HexComponent> m_Top;

	int m_HexWidth;
	int m_HexHeight;

	
};

