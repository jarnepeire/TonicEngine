#include "TonicEnginePCH.h"
#include "TonicEngine.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"

#include "InputLocator.h"

//Sound
#include "AudioLocator.h"
#include "SDLAudio.h"
#include "LogAudio.h"

//Commands
#include "Command.h"


//Components
#include "FPSComponent.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "ImageComponent.h"

//Game
#include "BaseGameThanol.h"

using namespace std;
using namespace std::chrono;

void Tonic::TonicEngine::Initialize(Tonic::BaseGameThanol* pGame)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	//Sound
	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error: " << Mix_GetError() << "\n";

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		pGame->GetWindowWidth(),
		pGame->GetWindowHeight(),
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	m_MsPerFrame = int(1000.f / pGame->GetCappedFPS());
}

/**
 * Code constructing the scene world starts here
 */
void Tonic::TonicEngine::LoadGame() const
{
}

void Tonic::TonicEngine::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Tonic::TonicEngine::Run(Tonic::BaseGameThanol* pGame)
{
	//Initializes the SDL Renderer, setup for window
	Initialize(pGame);

	//Tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	//Create all scenes, game objects, etc.
	pGame->CreateGameScenes();

	//Initialize scenes
	SceneManager::GetInstance().InitializeScenegraph();
	LoadGame();

	//Game Loop: http://gameprogrammingpatterns.com/game-loop.html
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		//auto& input = InputManager::GetInstance();

		auto previous = high_resolution_clock::now();
		float lag{};
		float ms_per_update = m_MsPerFrame / 1000.f;

		bool doContinue = true;
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			const float elapsed = duration_cast<duration<float>>(currentTime - previous).count();
			previous = currentTime;
			lag += elapsed;

			doContinue = InputLocator::GetInputManager().ProcessInput();
			//doContinue = input.ProcessInput();

			//Fixed Update
			while (lag >= ms_per_update)
			{
				sceneManager.FixedUpdate(ms_per_update);
				lag -= ms_per_update;
			}

			//Update
			sceneManager.Update(elapsed);
			renderer.Render();

			//Sleep if running too fast
			const auto sleepTime = currentTime + milliseconds(m_MsPerFrame) - high_resolution_clock::now();
			if (sleepTime.count() > 0.f)
				this_thread::sleep_for(sleepTime);
		}
	}
	Cleanup();
	
}
