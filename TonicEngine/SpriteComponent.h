#pragma once
#include "Component.h"
#include <SDL.h>

namespace dae
{
	class Texture2D;
}
class ImageComponent;

class SpriteComponent : public Component
{
public:

	enum class ESpriteAnimation : int
	{
		idle = 0,
		run = 1,
		jumping = 2,
		attacking = 3,
		dying = 4,
		respawn = 5
	};

	SpriteComponent(dae::GameObject* parent, const std::string& filename, int frameWidth, int frameHeight, int nbColumns, int animationSpeedInMS, float scale = 1.f);
	virtual ~SpriteComponent() = default;

	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	ESpriteAnimation& GetSpriteAnimationState() { return m_CurrentAnimation; }
	void SetSpriteAnimationState(ESpriteAnimation anim) { m_CurrentAnimation = anim; }
	void SetIsLeft(bool isLeft);

private:
	std::shared_ptr<dae::Texture2D> m_Texture{};
	SDL_Rect m_Dest;
	SDL_Rect m_Src;
	SDL_RendererFlip m_Flip;

	const int m_FrameWidth;
	const int m_FrameHeight;
	float m_Scale;
	const int m_NbColumns;
	const int m_AnimationSpeedInMS;
	ESpriteAnimation m_CurrentAnimation;
};

