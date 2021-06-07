#pragma once
#include "Component.h"
#include <SDL_pixels.h>
#include <string>

namespace Tonic
{
	class Font;
	class Texture2D;

	class TextComponent final : public Component
	{
	public:
		TextComponent(const std::string& text = "", const std::shared_ptr<Tonic::Font>& font = nullptr, const SDL_Color& color = SDL_Color{ 255,255,255 });
		virtual ~TextComponent() = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;


		void Initialize() override {}
		void PostInitialize() override {}
		void FixedUpdate(float) override {}
		void Update(float dt) override;
		void Render() override;

		/* Set text to render */
		void SetText(const std::string& text);

		/* Set font of text */
		void SetFont(std::shared_ptr<Tonic::Font> pFont);

		/* Set color of text */
		void SetColor(int r, int g, int b);

		/* Set color of text */
		void SetColor(SDL_Color c);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Tonic::Font> m_pFont;
		std::shared_ptr<Tonic::Texture2D> m_pTexture;
		SDL_Color m_Color;
	};

}