#pragma once
struct SDL_Window;
namespace dae
{
	class BaseGameThanol;
	class TonicEngine
	{
	public:
		void Initialize(dae::BaseGameThanol* pGame);
		void LoadGame() const;
		void Cleanup();
		void Run(dae::BaseGameThanol* pGame);
	private:
		int m_MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};
}