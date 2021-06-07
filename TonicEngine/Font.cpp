#include "TonicEnginePCH.h"
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* Tonic::Font::GetFont() const {
	return m_Font;
}

Tonic::Font::Font(const std::string& fullPath, unsigned int size) : m_Font(nullptr), m_Size(size)
{
	m_Font = TTF_OpenFont(fullPath.c_str(), size);
	if (m_Font == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

Tonic::Font::~Font()
{
	TTF_CloseFont(m_Font);
}
