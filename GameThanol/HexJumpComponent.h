#pragma once
#include <Component.h>
#include "HexComponent.h"

class HexGrid;

class HexJumpComponent : public Component
{
public:
	HexJumpComponent(dae::GameObject* parent, HexGrid* pHexGrid, int startRow, int startCol, float timeToJump = 1.f);
	virtual ~HexJumpComponent() = default;

	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	/* Describes the translation */
	void JumpTo(int rowTranslation, int colTranslation);
	bool IsJumping() const { return m_IsJumping; }

	void ResetToTop();

	const HexCoordinate& GetCurrentCoordinate() const { return m_CurrentCoordinate; }
	const HexCoordinate& GetJumpToCoordinate() const { return m_JumpToCoordinate; }
private:
	HexGrid* m_pHexGrid;
	HexCoordinate m_CurrentCoordinate;
	glm::vec2 m_InitPos;
	HexCoordinate m_JumpToCoordinate;
	glm::vec2 m_JumpToPos;
	glm::vec2 m_PosForArc;

	bool m_CanJump;
	bool m_IsJumping;
	bool m_NeedsRespawn;
	float m_JumpingTimer;
	float m_TimeToJump;

	//Analytic variables for arc
	float m_A;
	float m_B;
	float m_C;
	
};

