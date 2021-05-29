#pragma once
#include "Component.h"
#include <SDL.h>

namespace dae
{
	class Texture2D;
}
struct SDL_Renderer;

class RenderComponent : public Component
{
public:
	RenderComponent(dae::GameObject* parent, SDL_Renderer* pRenderer);
	virtual ~RenderComponent() = default;

	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	void RenderTexture(const dae::Texture2D& texture, float x, float y, float scale = 1.f) const;
	void RenderTexture(const dae::Texture2D& texture, float x, float y, float width, float height, float scale = 1.f) const;
	void RenderAnimation(const dae::Texture2D& texture, SDL_Rect& src, SDL_Rect& dest, SDL_RendererFlip& flip);

private:
	SDL_Renderer* m_pSDLRenderer;

};

