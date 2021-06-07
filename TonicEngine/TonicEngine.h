#pragma once
struct SDL_Window;
namespace Tonic
{
	class BaseGameThanol;
	class TonicEngine final
	{
	public:
		/* Runs the game */
		void Run(Tonic::BaseGameThanol* pGame);
	
	private:
		int m_MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};

		/* Initializes the engine's functionality and the game to be run in the engine */
		void Initialize(Tonic::BaseGameThanol* pGame);

		/* Does cleanup of memory and other managed objects */
		void Cleanup();
	};
}