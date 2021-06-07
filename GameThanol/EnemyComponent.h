#pragma once
#include <Component.h>

namespace Tonic
{
	class GameObject;
}

enum class EnemyType
{
	SamSlick,
	UggWrongway,
	Coily
};

class EnemyComponent : public Tonic::Component
{
public:

	EnemyComponent(Tonic::GameObject* parent, EnemyType enemyType, int defeatingScore, float minSpawnTime, float maxSpawnTime, unsigned int deathSoundId);
	virtual ~EnemyComponent() = default;

	void Initialize() override;
	void PostInitialize() override;
	void FixedUpdate(float dt) override {}
	void Update(float dt) override;
	void Render() override {}

	const EnemyType& GetEnemyType() const { return m_EnemyType; }

	void ResetEnemy();
	int GetDefeatingScore() const { return m_DefeatingScore; }
	void Kill();

private:
	EnemyType m_EnemyType;
	bool m_HasSpawned;
	float m_SpawnTimer;
	float m_MinSpawnTime;
	float m_MaxSpawnTime;
	float m_TimeToSpawn;

	bool m_CanFall;
	float m_FallTimer;
	float m_TimeToFall;
	glm::vec2 m_FallStartPos;
	glm::vec2 m_StartPos;

	int m_DefeatingScore;
	unsigned int m_DeathSoundID;
};

