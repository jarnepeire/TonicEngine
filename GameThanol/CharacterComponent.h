#pragma once
#include "Component.h"

class CharacterComponent : public Tonic::Component
{
public:
	CharacterComponent(Tonic::GameObject* parent);
	virtual ~CharacterComponent() = default;

	void Initialize() override;
	void PostInitialize() override;
	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	void GainScore(int score);
	int GetScore() const { return m_Score; }

	void ResetScore();
private:
	int m_Score;

};

