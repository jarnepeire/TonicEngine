#pragma once
#include "Component.h"
#include <SDL.h>

struct SDL_Renderer;

namespace Tonic
{
	class Texture2D;
	class RenderComponent final : public Component
	{
	public:
		RenderComponent(SDL_Renderer* pRenderer);
		virtual ~RenderComponent() = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void Initialize() override {}
		void PostInitialize() override {}
		void FixedUpdate(float) override {}
		void Update(float) override {}
		void Render() override {}

		/* Renders given texture at position 'x, y', using the original texture width/height with given scale applied */
		void RenderTexture(const Tonic::Texture2D& texture, float x, float y, float scale = 1.f) const;
		
		/* Renders given texture at position 'x, y', using a custom width/height with given scale applied */
		void RenderTexture(const Tonic::Texture2D& texture, float x, float y, float width, float height, float scale = 1.f) const;
		
		/* Renders the part 'src' of an animation spritesheet at position 'dest', given a render flip */
		void RenderAnimation(const Tonic::Texture2D& texture, SDL_Rect& src, SDL_Rect& dest, SDL_RendererFlip& flip) const;

	private:
		SDL_Renderer* m_pSDLRenderer;
	};

}