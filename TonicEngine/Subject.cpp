#include "TonicEnginePCH.h"
#include "Subject.h"
#include "GameObject.h"
#include "Observer.h"
#include <algorithm>

void Tonic::Subject::AddObserver(std::shared_ptr<Observer> pObserver)
{
	m_pObservers.push_back(pObserver);
}

void Tonic::Subject::RemoveObserver(std::shared_ptr<Observer> pObserver)
{
	auto itToRemove = std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver);
	m_pObservers.erase(itToRemove);
}

void Tonic::Subject::Notify(Tonic::GameObject* pGameObject, int eventId)
{
	std::for_each(m_pObservers.begin(), m_pObservers.end(), [&pGameObject, &eventId](std::shared_ptr<Observer> pObserver)
		{
			pObserver->Notify(pGameObject, eventId);
		});
}
