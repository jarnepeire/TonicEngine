#pragma once
#include "Component.h"
class TextComponent;

class HealthComponent : public Component
{
public:
	HealthComponent(dae::GameObject* parent, int nbLives);
	virtual ~HealthComponent() = default;

	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	void LoseLife();
	int GetNbLives() const { return m_NbLives; }

private:
	int m_NbLives;
};

