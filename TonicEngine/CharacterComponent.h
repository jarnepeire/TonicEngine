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
};

