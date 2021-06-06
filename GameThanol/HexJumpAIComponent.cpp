#include "HexJumpAIComponent.h"
#include "HexJumpComponent.h"
#include <GameObject.h>
#include "HexGrid.h"
#include "AudioLocator.h"
#include "SDLAudio.h"

HexJumpAIComponent::HexJumpAIComponent(dae::GameObject* parent, float postJumpWaitingTime, unsigned int jumpSoundId)
	: Component(parent)
	, m_HexJumpComponent()
	, m_IsActive(true)
	, m_CanWait(false)
	, m_WaitingTimer(0.f)
	, m_PostJumpWaitingTime(postJumpWaitingTime)
	, m_JumpSoundID(jumpSoundId)
{
}


void HexJumpAIComponent::Initialize()
{
}

void HexJumpAIComponent::PostInitialize()
{
	m_HexJumpComponent = m_pGameObject->GetComponent<HexJumpComponent>();
}

void HexJumpAIComponent::Update(float dt)
{
	if (!m_IsActive)
		return;

	if (m_CanWait)
	{
		m_WaitingTimer += dt;
		if (m_WaitingTimer >= m_PostJumpWaitingTime)
		{
			//Reset waiting timer 
			m_WaitingTimer = 0.f;
			m_CanWait = false;

			//Make next jump
			HexCoordinate hc = DetermineNextJump();
			m_HexJumpComponent->JumpTo(hc.Row, hc.Col);
			AudioLocator::GetAudioSystem().Play(m_JumpSoundID, 0.2f);
		}
	}
}

void HexJumpAIComponent::StartWaiting()
{
	m_CanWait = true;
}

void HexJumpAIComponent::ResetAI()
{
	m_IsActive = true;

	m_CanWait = false;
	m_WaitingTimer = 0.f;
}
