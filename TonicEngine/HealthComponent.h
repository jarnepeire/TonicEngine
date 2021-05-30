#pragma once
#include "Component.h"
class RespawnComponent;

class HealthComponent : public Component
{
public:
	HealthComponent(dae::GameObject* parent, int nbLives = 5);
	virtual ~HealthComponent() = default;

	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	void ResetLives();
	void LoseLife();
	int GetNbLives() const { return m_NbLives; }

	void SetRespawnComponent(std::shared_ptr<RespawnComponent> respawnComponent);
	bool HasDied() const { return m_HasDied; }
private:
	std::shared_ptr<RespawnComponent> m_RespawnComponent;
	int m_NbLives;
	int m_NbLivesOriginal;
	bool m_HasDied;
};

