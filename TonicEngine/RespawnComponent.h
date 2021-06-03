#pragma once
#include "Component.h"

class RespawnComponent : public Component
{
public:
	RespawnComponent(dae::GameObject* parent, const glm::vec2& respawnPos, float respawnTime = 3.f);
	virtual ~RespawnComponent() {}

	void Initialize() override;
	void PostInitialize() override;
	void FixedUpdate(float) override {}
	void Update(float dt) override;
	void Render() override {}

	void SetRespawnPosition(const glm::vec2& respawnPos) { m_RespawnPosition = respawnPos; }
	void SetRespawnTime(float time) { m_RespawnTime = time; }
	void Respawn();

	bool IsRespawning() const { return m_IsRespawning; }
private:
	glm::vec2 m_RespawnPosition;
	glm::vec2 m_InitPosition;
	bool m_CanRespawn;
	bool m_IsRespawning;
	float m_RespawnTime;
	float m_Timer;

};

