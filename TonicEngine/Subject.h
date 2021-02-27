#pragma once
#include <vector>

namespace dae { class GameObject; }
enum class Event;
class Observer;

class Subject
{
public:
	Subject() = default;
	~Subject();

	void AddObserver(Observer* pObserver);
	void RemoveObserver(Observer* pObserver);
	void Notify(dae::GameObject* pGameObject, Event e);

private:
	std::vector<Observer*> m_pObservers;

};

