#pragma once
#include <vector>
#include <memory>

namespace dae { class GameObject; }
enum class Event;
class Observer;

class Subject
{
public:
	Subject() = default;
	~Subject() = default;

	void AddObserver(std::shared_ptr<Observer> pObserver);
	void RemoveObserver(std::shared_ptr<Observer> pObserver);
	void Notify(dae::GameObject* pGameObject, Event e);

private:
	std::vector<std::shared_ptr<Observer>> m_pObservers;

};

