#pragma once
namespace dae
{
	class GameObject;
}

enum class Event
{
	EVENT_PLAYER_LOST_LIFE,
	EVENT_PLAYER_SCORED
};

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void Notify(dae::GameObject* object, Event e) = 0;
};