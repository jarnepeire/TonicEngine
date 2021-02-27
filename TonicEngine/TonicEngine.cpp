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

//Components
#include "FPSComponent.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "ImageComponent.h"
#include "HealthComponent.h"
#include "CharacterComponent.h"

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
	//Scene
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//Fonts
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);
	auto qBertFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

	//Background
	auto bgObject = std::make_shared<GameObject>();
	bgObject->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(bgObject.get(), "background.jpg"));
	bgObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(bgObject.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	scene.Add(bgObject);

	//Logo
	auto logoObject = std::make_shared<GameObject>();
	logoObject->SetPosition(216, 180);
	logoObject->AddComponent<ImageComponent>(std::make_shared<ImageComponent>(logoObject.get(), "logo.png"));
	logoObject->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(logoObject.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	scene.Add(logoObject);

	//Header text
	auto to = std::make_shared<GameObject>();
	to->SetPosition(80, 20);
	to->AddComponent<TextComponent>(std::make_shared<TextComponent>(to.get(), "Programming 4 Assignment", font));
	to->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(to.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	scene.Add(to);

	//FPS game object
	auto fpsCounter = std::make_shared<GameObject>();
	fpsCounter->SetPosition(30, 15);
	fpsCounter->AddComponent<FPSComponent>(std::make_shared<FPSComponent>(fpsCounter.get(), fpsFont));
	fpsCounter->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(fpsCounter.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	scene.Add(fpsCounter);

	//Q-Bert
	auto qBert = std::make_shared<GameObject>();
	qBert->SetPosition(30, 100);
	qBert->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(qBert.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	auto pTextQBert = qBert->AddComponent<TextComponent>(std::make_shared<TextComponent>(qBert.get(), "Lives", qBertFont));
	qBert->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(qBert.get(), 5, pTextQBert));
	qBert->AddComponent<CharacterComponent>(std::make_shared<CharacterComponent>(qBert.get()));
	scene.Add(qBert);
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
	//Initializes the SDL Renderer, setup for window
	Initialize();

	//Tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	//Create all game objects
	LoadGame();

	//Game Loop: http://gameprogrammingpatterns.com/game-loop.html
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

			//Fixed Update
			while (lag >= ms_per_update)
			{
				sceneManager.FixedUpdate(ms_per_update);
				lag -= ms_per_update;
			}

			sceneManager.Update(elapsed);
			renderer.Render();

			//Sleep if running too fast
			const auto sleepTime = currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now();
			if (sleepTime.count() > 0.f)
				this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
