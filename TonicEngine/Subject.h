#pragma once
#include <vector>
#include <memory>
#include "Event.h"

namespace Tonic
{
	class GameObject;
	class Observer;

	class Subject final
	{
	public:
		Subject() = default;
		~Subject() = default;

		void AddObserver(std::shared_ptr<Observer> pObserver);
		void RemoveObserver(std::shared_ptr<Observer> pObserver);
		void Notify(Tonic::GameObject* pGameObject, int eventId);

	private:
		std::vector<std::shared_ptr<Observer>> m_pObservers;
	};
}