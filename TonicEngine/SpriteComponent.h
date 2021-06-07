#pragma once
#include "Component.h"
#include <SDL.h>
#include <string>

namespace Tonic
{
	class Texture2D;
	class GameObject;
	class ImageComponent;

	class SpriteComponent final : public Component
	{
	public:

		SpriteComponent(const std::string& filename, int frameWidth, int frameHeight, int nbColumns, int animationSpeedInMS, float scale = 1.f);
		virtual ~SpriteComponent() = default;
		
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Initialize() override;
		void PostInitialize() override {}
		void FixedUpdate(float) override {}
		void Update(float dt) override;
		void Render() override;

		/* Gets current row of sprites being used in the animation spritesheet */
		const int GetCurrentAnimationRow() const { return m_CurrentAnimationRow; }

		/* Return the width of one sprite frame */
		const int GetFrameWidth() const { return m_FrameWidth; }

		/* Return the height of one sprite frame */
		const int GetFrameHeight() const { return m_FrameHeight; }

		/* Set whether the spritesheet can be rendered or not */
		void SetEnableRender(bool b) { m_EnableRender = b; }

		/* Sets row of sprites that needs to be used in the animation spritesheet */
		void SetAnimationRow(int animRow) { m_CurrentAnimationRow = animRow; }

		/* Set whether the sprite should be flipped */
		void SetIsFlipped(bool isFlipped);

	private:
		bool m_EnableRender;
		std::shared_ptr<Tonic::Texture2D> m_pTexture{};
		SDL_Rect m_Dest;
		SDL_Rect m_Src;
		SDL_RendererFlip m_Flip;

		const int m_FrameWidth;
		const int m_FrameHeight;
		float m_Scale;
		const int m_NbColumns;
		const int m_AnimationSpeedInMS;
		int m_CurrentAnimationRow;
	};

}