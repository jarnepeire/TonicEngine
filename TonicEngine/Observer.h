#pragma once
namespace dae
{
	class GameObject;
}

enum class Event
{
	EVENT_ACTOR_LOST_LIFE,
	EVENT_ACTOR_SCORED
};

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void Notify(dae::GameObject* object, Event e) = 0;
};

class CharacterObserver : public Observer
{
public:
	virtual ~CharacterObserver() = default;
	void Notify(dae::GameObject* object, Event e) override;

};

