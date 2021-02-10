#include "TonicEnginePCH.h"
#include "TonicEngine.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

//Components
#include "FPSComponent.h"
#include "TextComponent.h"

using namespace std;
using namespace std::chrono;

void dae::TonicEngine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::TonicEngine::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//Fonts
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);

	
	auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);

	auto fpsCounter = std::make_shared<GameObject>();
	fpsCounter->SetPosition(30, 15);
	fpsCounter->AddComponent(std::make_shared<FPSComponent>(fpsCounter.get(), fpsFont));
	fpsCounter->GetComponent<FPSComponent>()->DisplayFPS(true);
	scene.Add(fpsCounter);
}

void dae::TonicEngine::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::TonicEngine::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		auto previous = high_resolution_clock::now();
		float lag{};
		float ms_per_update = MsPerFrame / 1000.f;

		bool doContinue = true;
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			const float elapsed = duration_cast<duration<float>>(currentTime - previous).count();
			previous = currentTime;
			lag += elapsed;

			doContinue = input.ProcessInput();
			while (lag >= ms_per_update)
			{
				sceneManager.Update(ms_per_update);
				lag -= ms_per_update;
			}

			renderer.Render();
		}
	}

	Cleanup();
}
