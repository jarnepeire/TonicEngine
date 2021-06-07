#include "DiskComponent.h"
#include <SpriteComponent.h>
#include <GameObject.h>
#include <MathHelper.h>
#include "HexGrid.h"
#include "HexComponent.h"
#include "HexJumpComponent.h"
#include <AudioLocator.h>

using namespace Tonic;
DiskComponent::DiskComponent(float timeToMove, std::shared_ptr<HexGrid> hexGrid, const HexCoordinate& hc)
	: Component()
	, m_Grid(hexGrid)
	, m_CanMove(false)
	, m_pObjectToMove(nullptr)
	, m_StartPosition()
	, m_MoveToPosition()
	, m_Timer(0.f)
	, m_TimeToMove(timeToMove)
	, m_AttachedHexCoordinate(hc)
	, m_MovingSoundID()
{
}

void DiskComponent::Initialize()
{
}

void DiskComponent::PostInitialize()
{
	AttachToGrid(m_Grid, m_AttachedHexCoordinate);
}

void DiskComponent::FixedUpdate(float dt)
{
}

void DiskComponent::Update(float dt)
{
	if (m_CanMove)
	{
		m_Timer += dt;
		if (m_Timer > m_TimeToMove)
		{
			m_Timer = 0.f;
			m_CanMove = false;
			const auto& topPos = m_Grid->GetTop()->GetHexPosition();
			m_pGameObject->GetTransform().SetPosition(topPos.x, topPos.y, 0.f);

			m_pObjectToMove->GetTransform().SetPosition(topPos.x, topPos.y, 0.f);
			m_pObjectToMove->GetComponent<HexJumpComponent>()->SetIsBeingCarried(false);
			m_pObjectToMove->GetComponent<HexJumpComponent>()->ResetToTop();

			m_Grid->RemoveDisk(this, m_AttachedHexCoordinate);
		}
		else
		{
			//Move object to top position
			float timeToLerpAlpha = (1.f / m_TimeToMove) * m_Timer;
			float toX = FLerp(m_StartPosition.x, m_MoveToPosition.x, timeToLerpAlpha);
			float toY = FLerp(m_StartPosition.y, m_MoveToPosition.y, timeToLerpAlpha);
			m_pGameObject->GetTransform().SetPosition(toX, toY, 0.f);
			m_pObjectToMove->GetTransform().SetPosition(toX, toY, 0.f);
		}
	}
}

void DiskComponent::Render()
{
}

void DiskComponent::Move(Tonic::GameObject* pObjToMove, const glm::vec2& toPosition)
{
	m_CanMove = true;
	m_pObjectToMove = pObjToMove;
	m_StartPosition = pObjToMove->GetTransform().GetPosition();
	m_MoveToPosition = toPosition;
	m_pObjectToMove->GetComponent<HexJumpComponent>()->SetIsBeingCarried(true);

	//Play moving sound
	AudioLocator::GetAudioSystem().Play(m_MovingSoundID, 0.2f);
}

void DiskComponent::AttachToGrid(std::shared_ptr<HexGrid> hexGrid, const HexCoordinate& hc)
{
	if (m_Grid)
	{
		m_Grid->RemoveDisk(this, m_AttachedHexCoordinate);
	}

	m_AttachedHexCoordinate = hc;
	m_Grid = hexGrid;
	m_Grid->AddDisk(this, m_AttachedHexCoordinate);
}
