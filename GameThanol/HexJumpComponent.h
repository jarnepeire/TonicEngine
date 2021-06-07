#pragma once
#include <Component.h>
#include "HexCoordinate.h"

class HexGrid;

class HexJumpComponent : public Tonic::Component
{
public:
	HexJumpComponent(Tonic::GameObject* parent, HexGrid* pHexGrid, int startRow, int startCol, float timeToJump = 1.f);
	virtual ~HexJumpComponent() = default;

	void Initialize() override;
	void PostInitialize() override;
	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	/* Describes the translation */
	void JumpTo(int rowTranslation, int colTranslation);
	bool IsJumping() const { return m_IsJumping; }

	void ResetToOriginalCoordinate();
	void ResetToTop();

	HexGrid* GetGrid() { return m_pHexGrid; }
	const HexCoordinate& GetPreviousCoordinate() const { return m_PreviousCoordinate; }
	const HexCoordinate& GetCurrentCoordinate() const { return m_CurrentCoordinate; }
	const HexCoordinate& GetJumpToCoordinate() const { return m_JumpToCoordinate; }

	bool IsBeingCarried() const { return m_IsBeingCarried; }
	void SetIsBeingCarried(bool b) { m_IsBeingCarried = b; }

	bool NeedsRespawn() const { return m_NeedsRespawn; }

private:
	HexGrid* m_pHexGrid;
	HexCoordinate m_OriginalStartCoordinate;
	HexCoordinate m_PreviousCoordinate;
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
	bool m_IsBeingCarried;
	bool m_IsSavedByDisk;

	//Analytic variables for arc
	float m_A;
	float m_B;
	float m_C;
	
};

