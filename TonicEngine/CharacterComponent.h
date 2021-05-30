#pragma once
#include "Component.h"
class TextComponent;

class CharacterComponent : public Component
{
public:
	CharacterComponent(dae::GameObject* parent);
	virtual ~CharacterComponent() = default;

	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	void GainScore(int score);
	int GetScore() const { return m_Score; }

	void ResetScore();
private:
	int m_Score;

};

