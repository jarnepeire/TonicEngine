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

using namespace dae;
HexJumpComponent::HexJumpComponent(dae::GameObject* parent, HexGrid* pHexGrid, int startRow, int startCol, float timeToJump)
	: Component(parent)
	, m_pHexGrid(pHexGrid)
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
{
	glm::vec2 hexPos{};
	m_pHexGrid->GetHexPosition(m_CurrentCoordinate, hexPos);
	m_pGameObject->SetPosition(hexPos.x, hexPos.y);
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
			m_CurrentCoordinate = m_JumpToCoordinate;

			//TODO: Reset animation to idle
			//...
			m_pGameObject->GetTransform().SetPosition(m_JumpToPos.x, m_JumpToPos.y, 0.f);

			//Notify lost life and reset for next position attempt
			if (m_NeedsRespawn)
			{
				m_NeedsRespawn = false;
				m_CurrentCoordinate = m_pHexGrid->GetTop()->GetHexCoordinate();
				m_InitPos = m_pHexGrid->GetTop()->GetHexPosition();

				auto pHealth = m_pGameObject->GetComponent<HealthComponent>();
				if (pHealth)
					pHealth->LoseLife();
			}
		}
		else
		{
			//TODO: move object and make sure animation is set to jumping
			//Moving object
			m_IsJumping = true;

			float timeToLerpAlpha = (m_JumpingTimer / m_TimeToJump);
			glm::vec2 toPos = Vec2ParabolaLerp(m_InitPos, m_JumpToPos, m_A, m_B, m_C, timeToLerpAlpha);
			m_pGameObject->GetTransform().SetPosition(toPos.x, toPos.y, 0.f);
			
			//float timeToLerpAlpha = (1.f / m_TimeToJump) * m_JumpingTimer;
			//float toX = FLerp(m_InitPos.x, m_JumpToPos.x, timeToLerpAlpha);
			//float toY = FLerp(m_InitPos.y, m_JumpToPos.y, timeToLerpAlpha);
			//m_pGameObject->GetTransform().SetPosition(toX, toY, 0.f);
		}
	}
}

void HexJumpComponent::Render()
{
}

void HexJumpComponent::JumpTo(int rowTranslation, int colTranslation)
{
	//If we're still respawning, we can't do anything
	if (m_pGameObject->GetComponent<RespawnComponent>()->IsRespawning())
		return;

	//Can only jump to the next hex if we're standing still on a hex
	if (m_IsJumping)
		return;

	//Continue setup for jump
	m_CanJump = true;
	m_InitPos = m_pGameObject->GetTransform().GetPosition();
	m_JumpToCoordinate = HexCoordinate(m_CurrentCoordinate.Row + rowTranslation, m_CurrentCoordinate.Col + colTranslation);
	bool isValidHex = m_pHexGrid->GetHexPosition(m_JumpToCoordinate, m_JumpToPos);
	if (!isValidHex)
	{
		//Notify for lost life
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

	//If hex was valid, create offsetted third position as an "inbetween" position to form an arc that will define its movement
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
}
