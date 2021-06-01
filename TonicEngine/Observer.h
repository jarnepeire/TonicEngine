#pragma once
#include "Event.h"
namespace dae
{
	class GameObject;
}

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void Notify(dae::GameObject* object, Event e) = 0;

protected:
	Observer() = default;
};