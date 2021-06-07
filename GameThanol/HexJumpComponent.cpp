#include "HexJumpComponent.h"
#include <GameObject.h>
#include "HexGrid.h"
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include "MathHelper.h"
#include <HealthComponent.h>
#include "QBertGame.h"
#include "SpriteComponent.h"
#include "RespawnComponent.h"
#include "CharacterComponent.h"
#include "Event.h"
#include "DiskComponent.h"
#include "GameScores.h"
#include "HexComponent.h"

using namespace dae;
HexJumpComponent::HexJumpComponent(dae::GameObject* parent, HexGrid* pHexGrid, int startRow, int startCol, float timeToJump)
	: Component(parent)
	, m_OriginalStartCoordinate(HexCoordinate(startRow, startCol))
	, m_pHexGrid(pHexGrid)
	, m_PreviousCoordinate(HexCoordinate())
	, m_CurrentCoordinate(HexCoordinate(startRow, startCol))
	, m_JumpToCoordinate(HexCoordinate())
	, m_CanJump(false)
	, m_IsJumping(false)
	, m_NeedsRespawn(false)
	, m_JumpingTimer(0.f)
	, m_TimeToJump(timeToJump)
	, m_PosForArc()
	, m_A()
	, m_B()
	, m_C()
	, m_IsBeingCarried(false)
	, m_IsSavedByDisk(false)
{
}

void HexJumpComponent::Initialize()
{
	glm::vec2 hexPos{};
	m_pHexGrid->GetHexPosition(m_CurrentCoordinate, hexPos);
	m_pGameObject->SetPosition(hexPos.x, hexPos.y);
}

void HexJumpComponent::PostInitialize()
{
}

void HexJumpComponent::FixedUpdate(float dt)
{
}

void HexJumpComponent::Update(float dt)
{
	if (m_CanJump)
	{
		m_JumpingTimer += dt;
		if (m_JumpingTimer >= m_TimeToJump)
		{
			//Reset jumping possibility
			m_JumpingTimer = 0.f;
			m_CanJump = false;
			m_IsJumping = false;
			m_PreviousCoordinate = m_CurrentCoordinate;
			m_CurrentCoordinate = m_JumpToCoordinate;
			m_pGameObject->GetTransform().SetPosition(m_JumpToPos.x, m_JumpToPos.y, 0.f);
			
			//If applicable notify it was saved by a disk
			if (m_IsSavedByDisk)
			{
				m_IsSavedByDisk = false;
				m_pSubject->Notify(m_pGameObject, Event::EVENT_JUMPER_SAVED_BY_DISK);
			}
			//Else if applicable notify lost life and reset coordinates/positions
			else if (m_NeedsRespawn)
			{
				m_NeedsRespawn = false;
				m_pSubject->Notify(m_pGameObject, Event::EVENT_JUMPER_FELL_OFF_GRID);
			}
			//Otherwise it moved to the next hex and can be awarded for it
			else
			{
				//Notify color change when hex isn't fully visited yet
				if (!m_pHexGrid->IsHexVisited(m_JumpToCoordinate))
				{
					m_pSubject->Notify(m_pGameObject, Event::EVENT_JUMPER_COLOR_CHANGE);
				}

				//Mark a visit and notify it landed
				//m_pHexGrid->VisitHex(m_JumpToCoordinate);
				m_pSubject->Notify(m_pGameObject, Event::EVENT_JUMPER_LANDED);
			}
		}
		else
		{
			//Moving object
			m_IsJumping = true;

			float timeToLerpAlpha = (m_JumpingTimer / m_TimeToJump);
			glm::vec2 toPos = Vec2ParabolaLerp(m_InitPos, m_JumpToPos, m_A, m_B, m_C, timeToLerpAlpha);
			m_pGameObject->GetTransform().SetPosition(toPos.x, toPos.y, 0.f);
		}
	}
}

void HexJumpComponent::Render()
{
}

void HexJumpComponent::JumpTo(int rowTranslation, int colTranslation)
{
	if (m_IsBeingCarried)
		return;

	//Setup for jump
	m_CanJump = true;
	m_InitPos = m_pGameObject->GetTransform().GetPosition();
	m_JumpToCoordinate = HexCoordinate(m_CurrentCoordinate.Row + rowTranslation, m_CurrentCoordinate.Col + colTranslation);
	bool isValidHex = m_pHexGrid->GetHexPosition(m_JumpToCoordinate, m_JumpToPos);
	if (!isValidHex)
	{
		//Check if there's a disk to save QBert's life
		auto pCurrentHex = m_pHexGrid->GetHexComponent(m_CurrentCoordinate);
		if (pCurrentHex)
		{
			auto pDisk = pCurrentHex->GetNeighbouringDisk();
			if (pDisk)
			{
				m_JumpToPos = pDisk->GetWorldPosition();
				m_IsSavedByDisk = true;
			}
			else
			{
				//Set flag for lost life
				m_NeedsRespawn = true;

				//Translate to left or right depending on movement
				int rowTrans = -1 * rowTranslation;
				if (colTranslation == 0)
				{
					rowTrans = -rowTrans;
				}
				m_JumpToPos.x = m_InitPos.x + (rowTrans * m_pHexGrid->GetHexWidth() * 2.f);

				//So that he falls down to the button of the map
				float windowHeight = (float)QBertGame::GetInstance().GetWindowHeight();
				float spriteHeight = (float)m_pGameObject->GetComponent<SpriteComponent>()->GetFrameHeight();
				m_JumpToPos.y = windowHeight + spriteHeight;
			}
		}

	}
	
	//Create offsetted third position as an "inbetween" position to form an arc that will define its movement
	int horizontal = (m_InitPos.x > m_JumpToPos.x) ? -1 : 1;
	int vertical = (m_InitPos.y > m_JumpToPos.y) ? -1 : 1;
	m_PosForArc.x = m_InitPos.x + (horizontal * (abs(m_InitPos.x - m_JumpToPos.x)) / 2.f);
	if (horizontal == -1 && vertical == 1)
	{
		m_PosForArc.y = m_InitPos.y;
	}
	else if (horizontal == 1 && vertical == -1)
	{
		m_PosForArc.y = m_JumpToPos.y;
	}
	else if (horizontal == 1 && vertical == 1)
	{
		m_PosForArc.y = m_InitPos.y;
	}
	else if (horizontal == -1 && vertical == -1)
	{
		m_PosForArc.y = m_JumpToPos.y;
	}

	//Adjust variables that define the arc the hex jumper will travel on
	//Initially made on desmos and used as a source here: https://www.desmos.com/calculator/lac2i0bgum
	float a1 = -(m_InitPos.x * m_InitPos.x) + (m_PosForArc.x * m_PosForArc.x);
	float b1 = -m_InitPos.x + m_PosForArc.x;
	float d1 = -m_InitPos.y + m_PosForArc.y;

	float a2 = -(m_PosForArc.x * m_PosForArc.x) + (m_JumpToPos.x * m_JumpToPos.x);
	float b2 = -m_PosForArc.x + m_JumpToPos.x;
	float d2 = -m_PosForArc.y + m_JumpToPos.y;

	float bMultiplier = -(b2 / b1);
	float a3 = bMultiplier * a1 + a2;
	float d3 = bMultiplier * d1 + d2;

	m_A = d3 / a3;
	m_B = (d1 - a1 * m_A) / b1;
	m_C = m_InitPos.y - m_A * (m_InitPos.x * m_InitPos.x) - m_B * m_InitPos.x;

	//Notify that jumper has jumped
	m_pSubject->Notify(m_pGameObject, Event::EVENT_JUMPER_JUMPED);
}

void HexJumpComponent::ResetToOriginalCoordinate()
{
	m_JumpingTimer = 0.f;
	m_CanJump = false;
	m_IsJumping = false;

	m_CurrentCoordinate = m_OriginalStartCoordinate;
	m_pHexGrid->GetHexPosition(m_CurrentCoordinate, m_InitPos);
	m_pGameObject->SetPosition(m_InitPos.x, m_InitPos.y);
}

void HexJumpComponent::ResetToTop()
{
	m_JumpingTimer = 0.f;
	m_CanJump = false;
	m_IsJumping = false;

	m_CurrentCoordinate = m_pHexGrid->GetTop()->GetHexCoordinate();
	m_pHexGrid->GetHexPosition(m_CurrentCoordinate, m_InitPos);
	m_pGameObject->SetPosition(m_InitPos.x, m_InitPos.y);
}
