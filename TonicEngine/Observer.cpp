#include "TonicEnginePCH.h"
#include "Observer.h"
#include "GameObject.h"
#include "CharacterComponent.h"
#include "TextComponent.h"
#include "HealthComponent.h"
#include "Renderer.h"

void CharacterObserver::Notify(dae::GameObject* object, Event e)
{
	if (Event::EVENT_ACTOR_LOST_LIFE == e)
	{
		auto health = object->GetComponent<HealthComponent>();
		if (health != nullptr)
		{
			health->LoseLife();
			if (health->IsDisplayingText())
			{
				health->GetHealthTextComponent()->SetText("Lives: " + std::to_string(health->GetNbLives()));
			}
		}
	}

	//switch (e)
	//{
	//case Event::EVENT_ACTOR_LOST_LIFE:
	//{
	//	auto health = object->GetComponent<HealthComponent>();
	//}
	//	//auto health = object->GetComponent<HealthComponent>();
	//	std::cout << "Player Lost Life\n";
	//	//object->GetComponent<CharacterComponent>()->Die();
	//	
	//	break;
	//
	//default:
	//	break;
	//}

	
}
