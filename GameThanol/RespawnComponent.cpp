#include "TonicEnginePCH.h"
#include "RespawnComponent.h"
#include "MathHelper.h"
#include <GameObject.h>

using namespace Tonic;
RespawnComponent::RespawnComponent(const glm::vec2& respawnPos, float respawnTime)
	: Component()
	, m_RespawnPosition(respawnPos)
	, m_InitPosition(glm::vec2(respawnPos.x, -35.f)) //offset above screen
	, m_CanRespawn(false)
	, m_RespawnTime(respawnTime)
	, m_IsRespawning(false)
	, m_Timer(0.f)
{
}

void RespawnComponent::Initialize()
{
}

void RespawnComponent::PostInitialize()
{
}

void RespawnComponent::Update(float dt)
{
	if (m_CanRespawn)
	{
		m_Timer += dt;
		if (m_Timer >= m_RespawnTime)
		{
			m_Timer = 0.f;
			m_IsRespawning = false;
			m_CanRespawn = false;
			m_pGameObject->GetTransform().SetPosition(m_RespawnPosition.x, m_RespawnPosition.y, 0.f);
		}
		else
		{
			m_IsRespawning = true;

			//Move object to respawn position
			float timeToLerpAlpha = (1.f / m_RespawnTime) * m_Timer;
			float toX = FLerp(m_InitPosition.x, m_RespawnPosition.x, timeToLerpAlpha);
			float toY = FLerp(m_InitPosition.y, m_RespawnPosition.y, timeToLerpAlpha);
			m_pGameObject->GetTransform().SetPosition(toX, toY, 0.f);
		}
	}
}

void RespawnComponent::Respawn()
{
	m_CanRespawn = true;
}
