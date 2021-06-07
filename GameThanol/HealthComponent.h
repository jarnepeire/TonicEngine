#pragma once
#include <Component.h>
class RespawnComponent;

class HealthComponent final : public Tonic::Component
{
public:
	HealthComponent(int nbLives = 5);
	virtual ~HealthComponent() = default;

	void Initialize() override;
	void PostInitialize() override;
	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	void SetNbLives(int lives);
	void ResetLives();
	void LoseLife();
	int GetNbLives() const { return m_NbLives; }

	void SetRespawnComponent(const std::shared_ptr<RespawnComponent>& respawnComponent);
	bool HasDied() const { return m_HasDied; }
private:
	std::shared_ptr<RespawnComponent> m_RespawnComponent;
	int m_NbLives;
	int m_NbLivesOriginal;
	bool m_HasDied;
};

