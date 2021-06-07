#pragma once
#include "Transform.h"
#include "Component.h"
#include <SDL_pixels.h>

namespace Tonic
{
	class Font;
	class Texture2D;
	class GameObject;


	class TextComponent : public Component
	{
	public:
		TextComponent(Tonic::GameObject* parent, const std::string& text = "", const std::shared_ptr<Tonic::Font>& font = nullptr, const SDL_Color& color = SDL_Color{ 255,255,255 });
		virtual ~TextComponent() = default;

		void Initialize() override;
		void PostInitialize() override;
		void FixedUpdate(float dt) override;
		void Update(float dt) override;
		void Render() override;

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Tonic::Font> pFont);
		void SetColor(int r, int g, int b);
		void SetColor(SDL_Color c);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Tonic::Font> m_Font;
		std::shared_ptr<Tonic::Texture2D> m_Texture;
		SDL_Color m_Color;
	};

}