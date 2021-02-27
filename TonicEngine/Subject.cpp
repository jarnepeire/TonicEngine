#include "TonicEnginePCH.h"
#include "Subject.h"
#include "GameObject.h"
#include "Observer.h"
#include <algorithm>

Subject::~Subject()
{
	std::for_each(m_pObservers.begin(), m_pObservers.end(), [](Observer* pObserver)
		{
			if (pObserver) delete pObserver;
		});
}

void Subject::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(std::move(pObserver));
}

void Subject::RemoveObserver(Observer* pObserver)
{
	auto itToRemove = std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver);
	m_pObservers.erase(itToRemove);
}

void Subject::Notify(dae::GameObject* pGameObject, Event e)
{
	std::for_each(m_pObservers.begin(), m_pObservers.end(), [&pGameObject, &e](Observer* pObserver)
		{
			pObserver->Notify(pGameObject, e);
		});
}
