#pragma once
#include "Component.h"

struct SDL_Window;
struct SDL_Renderer;

class RenderComponent : public Component
{
public:
	RenderComponent(dae::GameObject* parent);
	virtual ~RenderComponent() = default;

	void Update(float dt) override;
	void Render() override;
};

