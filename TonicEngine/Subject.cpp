#include "TonicEnginePCH.h"
#include "Subject.h"
#include "GameObject.h"
#include "Observer.h"
#include <algorithm>

void Subject::AddObserver(std::shared_ptr<Observer> pObserver)
{
	m_pObservers.push_back(pObserver);
}

void Subject::RemoveObserver(std::shared_ptr<Observer> pObserver)
{
	auto itToRemove = std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver);
	m_pObservers.erase(itToRemove);
}

void Subject::Notify(dae::GameObject* pGameObject, Event e)
{
	std::for_each(m_pObservers.begin(), m_pObservers.end(), [&pGameObject, &e](std::shared_ptr<Observer> pObserver)
		{
			pObserver->Notify(pGameObject, e);
		});
}
