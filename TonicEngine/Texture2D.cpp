#include "TonicEnginePCH.h"
#include "Texture2D.h"
#include <SDL.h>

Tonic::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

SDL_Texture* Tonic::Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}

Tonic::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_pTexture = texture;
}
