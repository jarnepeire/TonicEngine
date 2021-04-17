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

//Sound
#include "AudioLocator.h"
#include "SDLAudio.h"
#include "LogAudio.h"

//Commands
#include "Command.h"

//Observers
#include "HealthDisplay.h"
#include "ScoreDisplay.h"

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

	//Sound
	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error: " << Mix_GetError() << "\n";

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
	auto& input = InputManager::GetInstance();

	//Fonts
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);
	auto qBertBigFont = ResourceManager::GetInstance().LoadFont("CooperBlack.otf", 28);
	auto qBertSmallFont = ResourceManager::GetInstance().LoadFont("CooperBlack.otf", 22);

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

	// ------- Player 1 ------- //
	//Display Game Object (owns text components for UI)
	auto qBertDisplay = std::make_shared<GameObject>();;
	qBertDisplay->SetPosition(30, 100);
	
	qBertDisplay->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(qBertDisplay.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	qBertDisplay->AddComponent<TextComponent>(std::make_shared<TextComponent>(qBertDisplay.get(), "Player 1 -- Buttons: A/B", qBertBigFont));
	auto healthTextComp = qBertDisplay->AddComponent<TextComponent>(std::make_shared<TextComponent>(qBertDisplay.get(), "Lives: 5", qBertSmallFont));
	healthTextComp->SetPosition(0, 30); //Servers a translation relative to the parent object
	auto scoreTextComp = qBertDisplay->AddComponent<TextComponent>(std::make_shared<TextComponent>(qBertDisplay.get(), "Score: 0", qBertSmallFont));
	scoreTextComp->SetPosition(0, 55); //Servers a translation relative to the parent object
	scene.Add(qBertDisplay);
	
	//Observer -> link up the text components to display to (doesn't own two text components in this case)
	auto qBertHealthDisplay = std::make_shared<HealthDisplay>(healthTextComp);
	auto qBertScoreDisplay = std::make_shared<ScoreDisplay>(scoreTextComp);
	
	//Q-Bert itself, add components + add observer to components
	auto qBert = std::make_shared<GameObject>();
	
	int nbLives = 5;
	auto pHealth = qBert->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(qBert.get(), nbLives));
	pHealth->GetSubject()->AddObserver(qBertHealthDisplay);
	
	auto pChar = qBert->AddComponent<CharacterComponent>(std::make_shared<CharacterComponent>(qBert.get()));
	pChar->GetSubject()->AddObserver(qBertScoreDisplay);
	scene.Add(qBert);

	// ------- Player 2 ------- //
	//Display Game Object (owns text components for UI)
	auto p2UI = std::make_shared<GameObject>();;
	p2UI->SetPosition(30, 250);

	p2UI->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(p2UI.get(), dae::Renderer::GetInstance().GetSDLRenderer()));
	p2UI->AddComponent<TextComponent>(std::make_shared<TextComponent>(p2UI.get(), "Player 2 -- Buttons: X/Y", qBertBigFont));
	auto p2HealthTextComp = p2UI->AddComponent<TextComponent>(std::make_shared<TextComponent>(p2UI.get(), "Lives: 5", qBertSmallFont));
	p2HealthTextComp->SetPosition(0, 30);
	auto p2ScoreTextComp = p2UI->AddComponent<TextComponent>(std::make_shared<TextComponent>(p2UI.get(), "Score: 0", qBertSmallFont));
	p2ScoreTextComp->SetPosition(0, 55);
	scene.Add(p2UI);

	//Observer -> link up the text components to display to (doesn't own two text components in this case)
	auto p2HealthDisplay = std::make_shared<HealthDisplay>(p2HealthTextComp);
	auto p2ScoreDisplay = std::make_shared<ScoreDisplay>(p2ScoreTextComp);

	//Player itself, add components + add observer to components
	auto p2 = std::make_shared<GameObject>();

	auto pHealthP2 = p2->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(p2.get(), nbLives));
	pHealthP2->GetSubject()->AddObserver(p2HealthDisplay);

	auto pCharP2 = p2->AddComponent<CharacterComponent>(std::make_shared<CharacterComponent>(p2.get()));
	pCharP2->GetSubject()->AddObserver(p2ScoreDisplay);
	scene.Add(p2);

	//Input
	input.AddInputAction(SDL_SCANCODE_A, ControllerButton::ButtonA, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<ScoreCommand>(qBert.get()));
	input.AddInputAction(SDL_SCANCODE_B, ControllerButton::ButtonB, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<DieCommand>(qBert.get()));

	input.AddInputAction(SDL_SCANCODE_X, ControllerButton::ButtonX, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<ScoreCommand>(p2.get()));
	input.AddInputAction(SDL_SCANCODE_Y, ControllerButton::ButtonY, ControllerButtonType::wButton, TriggerState::Pressed, std::make_shared<DieCommand>(p2.get()));

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

	//Audio system
	SDLAudio* pSDLAudio = new SDLAudio();
	pSDLAudio->AddSound(SoundID::PlayerScored, "../Data/Sounds/sfx_gain_score.wav");
	pSDLAudio->AddSound(SoundID::PlayerDied,"../Data/Sounds/sfx_death.wav");

	AudioSystem* pAudioSystem = new LogAudio(pSDLAudio);
	AudioLocator::RegisterAudioSystem(pAudioSystem);

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

			//Update
			sceneManager.Update(elapsed);
			renderer.Render();

			//Sleep if running too fast
			const auto sleepTime = currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now();
			if (sleepTime.count() > 0.f)
				this_thread::sleep_for(sleepTime);
		}
	}

	delete pAudioSystem;
	Cleanup();
	
}
