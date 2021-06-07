#include "EnemyComponent.h"
#include <GameObject.h>
#include "Event.h"
#include "HexJumpComponent.h"
#include "HexGrid.h"
#include "HexComponent.h"
#include <MathHelper.h>
#include "QBertGame.h"
#include <SpriteComponent.h>
#include "AudioLocator.h"

EnemyComponent::EnemyComponent(dae::GameObject* parent, EnemyType enemyType, int defeatingScore, float minSpawnTime, float maxSpawnTime, unsigned int deathSoundId)
	: Component(parent)
	, m_EnemyType(enemyType)
	, m_DefeatingScore(defeatingScore)
	, m_HasSpawned(false)
	, m_SpawnTimer(0.f)
	, m_MinSpawnTime(minSpawnTime)
	, m_MaxSpawnTime(maxSpawnTime)
	, m_TimeToSpawn()
	, m_CanFall(false)
	, m_FallTimer(0.f)
	, m_TimeToFall(0.5f)
	, m_FallStartPos()
	, m_StartPos()
	, m_DeathSoundID(deathSoundId)
{
}

void EnemyComponent::Initialize()
{
	//Calculate random value between floats: https://stackoverflow.com/questions/686353/random-float-number-generation
	//Needed to determine random spawn time
	m_TimeToSpawn = m_MinSpawnTime + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (m_MaxSpawnTime - m_MinSpawnTime)));
}

void EnemyComponent::PostInitialize()
{
	//Set positions to fall from sky to hex
	auto pHexJump = m_pGameObject->GetComponent<HexJumpComponent>();
	if (pHexJump)
	{
		const auto& currHc = pHexJump->GetCurrentCoordinate();
		pHexJump->GetGrid()->GetHexPosition(currHc, m_StartPos);
		m_pGameObject->SetPosition(m_StartPos.x, m_StartPos.y);

		//Depends on enemy
		float windowHeight = (float)QBertGame::GetInstance().GetWindowHeight();
		float spriteHeight = (float)m_pGameObject->GetComponent<SpriteComponent>()->GetFrameHeight();
		if (m_EnemyType == EnemyType::SamSlick)
		{
			m_FallStartPos.x = m_StartPos.x;
			m_FallStartPos.y = -spriteHeight * 2.f; //Falls from top outside screen
		}
		else if (m_EnemyType == EnemyType::UggWrongway)
		{
			m_FallStartPos.x = m_StartPos.x;
			m_FallStartPos.y = windowHeight + (spriteHeight * 2.f); //Falls from bottom outside screen
		}
		else //Coily
		{
			m_FallStartPos.x = m_StartPos.x;
			m_FallStartPos.y = -spriteHeight * 2.f; //Falls from top outside screen
		}
	}
	m_pGameObject->SetPosition(m_FallStartPos.x, m_FallStartPos.y);
}

void EnemyComponent::Update(float dt)
{
	if (!m_HasSpawned)
	{
		m_SpawnTimer += dt;
		if (m_SpawnTimer >= m_TimeToSpawn)
		{
			m_HasSpawned = true;
			m_SpawnTimer = 0.f;

			//Notify it is falling spawned
			m_pSubject->Notify(m_pGameObject, Event::EVENT_ENEMY_FALLS);
			m_CanFall = true;
		}
	}

	if (m_CanFall)
	{
		m_FallTimer += dt;
		if (m_FallTimer >= m_TimeToFall)
		{
			m_CanFall = false;
			m_FallTimer = 0.f;

			//Notify it has spawned
			m_pSubject->Notify(m_pGameObject, Event::EVENT_ENEMY_SPAWNED);
		}
		else
		{
			//Move from out the screen to the start block
			float timeToLerpAlpha = (1.f / m_TimeToFall) * m_FallTimer;
			float toX = FLerp(m_FallStartPos.x, m_StartPos.x, timeToLerpAlpha);
			float toY = FLerp(m_FallStartPos.y, m_StartPos.y, timeToLerpAlpha);
			m_pGameObject->GetTransform().SetPosition(toX, toY, 0.f);
		}
	}

}

void EnemyComponent::ResetEnemy()
{
	m_HasSpawned = false;
	m_SpawnTimer = 0.f;

	m_CanFall = false;
	m_FallTimer = 0.f;

	m_pGameObject->SetPosition(m_FallStartPos.x, m_FallStartPos.y);
}

void EnemyComponent::Kill()
{
	AudioLocator::GetAudioSystem().Play(m_DeathSoundID, 0.2f);
}
