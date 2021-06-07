#pragma once
#include "Event.h"
namespace Tonic
{
	class GameObject;

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(Tonic::GameObject* object, int eventId) = 0;

	protected:
		Observer() = default;
	};
}