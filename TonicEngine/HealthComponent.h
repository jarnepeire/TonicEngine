#pragma once
#include "Component.h"
class TextComponent;

class HealthComponent : public Component
{
public:
	HealthComponent(dae::GameObject* parent, int nbLives, const std::shared_ptr<TextComponent>& pTextComp);
	virtual ~HealthComponent() = default;

	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	void LoseLife();
	int GetNbLives() const { return m_NbLives; }
	
	const std::shared_ptr<TextComponent>& GetHealthTextComponent() { return m_pTextComponent; }
	bool IsDisplayingText() const { return m_DisplayText; }
	void SetDisplayText(bool enable) { m_DisplayText = enable; }

private:
	bool m_DisplayText;
	std::shared_ptr<TextComponent> m_pTextComponent;
	int m_NbLives;
};

