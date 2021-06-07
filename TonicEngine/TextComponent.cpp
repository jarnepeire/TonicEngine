#include "TonicEnginePCH.h"
#include "TextComponent.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "RenderComponent.h"

Tonic::TextComponent::TextComponent(Tonic::GameObject* parent, const std::string& text, const std::shared_ptr<Font>& font, const SDL_Color& color)
	: Component(parent)
	, m_NeedsUpdate(true)
	, m_Text(text)
	, m_Font(font)
	, m_Texture(nullptr)
	, m_Color(color)
{
}

void Tonic::TextComponent::Initialize()
{
}

void Tonic::TextComponent::PostInitialize()
{
}

void Tonic::TextComponent::FixedUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void Tonic::TextComponent::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void Tonic::TextComponent::Render()
{
	if (m_Texture != nullptr)
	{
		auto pRender = m_pGameObject->GetComponent<RenderComponent>();
		const auto pos = m_Transform.GetPosition() + m_pGameObject->GetTransform().GetPosition();
		pRender->RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void Tonic::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void Tonic::TextComponent::SetFont(std::shared_ptr<Tonic::Font> pFont)
{
	m_Font = pFont;
}

void Tonic::TextComponent::SetColor(int r, int g, int b)
{
	m_Color.r = (Uint8)r;
	m_Color.g = (Uint8)g;
	m_Color.b = (Uint8)b;
}

void Tonic::TextComponent::SetColor(SDL_Color c)
{
	m_Color = c;
}
