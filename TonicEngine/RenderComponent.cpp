#include "TonicEnginePCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

RenderComponent::RenderComponent(dae::GameObject* parent, SDL_Renderer* pRenderer)
	: Component(parent)
	, m_pSDLRenderer(pRenderer)
{
}

void RenderComponent::FixedUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void RenderComponent::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void RenderComponent::Render()
{
}

void RenderComponent::RenderTexture(const dae::Texture2D& texture, float x, float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(m_pSDLRenderer, texture.GetSDLTexture(), nullptr, &dst);
}

void RenderComponent::RenderTexture(const dae::Texture2D& texture, float x, float y, float width, float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(m_pSDLRenderer, texture.GetSDLTexture(), nullptr, &dst);
}

void RenderComponent::RenderAnimation(const dae::Texture2D& texture, SDL_Rect& src, SDL_Rect& dest, SDL_RendererFlip& flip)
{
	//Render with src
	SDL_RenderCopyEx(m_pSDLRenderer, texture.GetSDLTexture(), &src, &dest, NULL, NULL, flip);
}
