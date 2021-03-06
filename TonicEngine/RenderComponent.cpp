#include "TonicEnginePCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"

Tonic::RenderComponent::RenderComponent(SDL_Renderer* pRenderer)
	: Component()
	, m_pSDLRenderer(pRenderer)
{
}

void Tonic::RenderComponent::RenderTexture(const Tonic::Texture2D& texture, float x, float y, float scale) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	dst.w = static_cast<int>(dst.w * scale);
	dst.h = static_cast<int>(dst.h * scale);
	SDL_RenderCopy(m_pSDLRenderer, texture.GetSDLTexture(), nullptr, &dst);
}

void Tonic::RenderComponent::RenderTexture(const Tonic::Texture2D& texture, float x, float y, float width, float height, float scale) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width * scale);
	dst.h = static_cast<int>(height * scale);
	SDL_RenderCopy(m_pSDLRenderer, texture.GetSDLTexture(), nullptr, &dst);
}

void Tonic::RenderComponent::RenderAnimation(const Tonic::Texture2D& texture, SDL_Rect& src, SDL_Rect& dest, SDL_RendererFlip& flip) const
{
	//Render with src
	SDL_RenderCopyEx(m_pSDLRenderer, texture.GetSDLTexture(), &src, &dest, NULL, NULL, flip);
}
