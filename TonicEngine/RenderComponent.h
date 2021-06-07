#pragma once
#include "Component.h"
#include <SDL.h>

struct SDL_Renderer;

namespace Tonic
{
	class Texture2D;
	class RenderComponent : public Component
	{
	public:
		RenderComponent(Tonic::GameObject* parent, SDL_Renderer* pRenderer);
		virtual ~RenderComponent() = default;

		void Initialize() override;
		void PostInitialize() override;
		void FixedUpdate(float dt) override;
		void Update(float dt) override;
		void Render() override;

		void RenderTexture(const Tonic::Texture2D& texture, float x, float y, float scale = 1.f) const;
		void RenderTexture(const Tonic::Texture2D& texture, float x, float y, float width, float height, float scale = 1.f) const;
		void RenderAnimation(const Tonic::Texture2D& texture, SDL_Rect& src, SDL_Rect& dest, SDL_RendererFlip& flip);

	private:
		SDL_Renderer* m_pSDLRenderer;

	};

}