#pragma once
#include "HexComponent.h"
#include <glm/vec2.hpp>

class HexGrid : public Component
{
public:
	HexGrid(dae::GameObject* parent, const std::string& hexImagePath, const std::string& hexImageVisittedPath, int gridSize, int hexWidth, int hexHeight);
	virtual ~HexGrid() = default;

	virtual void FixedUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void Render() override;

	const std::shared_ptr<HexComponent>& GetTop() const { return m_Top; }
	bool GetHexPosition(const HexCoordinate& hc, glm::vec2& hexPos) const;
	void VisitHex(const HexCoordinate& hc);
	int GetHexWidth() const { return m_HexWidth; }
	int GetHexHeight() const { return m_HexHeight; }

	bool IsHexVisited(const HexCoordinate& hc);
	
private:
	std::shared_ptr<ImageComponent> m_ImageComponent;
	std::shared_ptr<ImageComponent> m_ImageComponentVisitted;
	int m_GridSize;
	std::vector<std::shared_ptr<HexComponent>> m_Grid;
	std::shared_ptr<HexComponent> m_Top;

	int m_HexWidth;
	int m_HexHeight;

	
};

