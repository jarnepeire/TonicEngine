#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace Tonic
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		Renderer();
		~Renderer() = default;

		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		/* Returns SDL renderer */
		SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }

		/* Returns SDL window */
		SDL_Window* GetSDLWindow() const { return m_pWindow; }

	private:
		SDL_Window* m_pWindow;
		SDL_Renderer* m_pRenderer;

		bool m_RenderImGui;
		bool m_ShowDemoWindow;
		void DisplayUI() const;
	};
}

