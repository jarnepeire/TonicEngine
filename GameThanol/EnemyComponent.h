#pragma once
#include <Component.h>

namespace dae
{
	class GameObject;
}

class EnemyComponent : public Component
{
public:
	enum class EnemyType
	{
		SamSlick,
		Coily
	};

	EnemyComponent(dae::GameObject* parent, EnemyType enemyType, int defeatingScore, float minSpawnTime, float maxSpawnTime);
	virtual ~EnemyComponent() = default;

	void Initialize() override;
	void PostInitialize() override;
	void FixedUpdate(float dt) override {}
	void Update(float dt) override;
	void Render() override {}

	const EnemyType& GetEnemyType() const { return m_EnemyType; }

	void ResetEnemy();
	int GetDefeatingScore() const { return m_DefeatingScore; }
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

};

