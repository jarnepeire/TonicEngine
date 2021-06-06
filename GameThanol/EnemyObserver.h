#pragma once
#include <Observer.h>
#include <memory>

class EnemyObserver : public Observer
{
public:
	EnemyObserver(std::shared_ptr<dae::GameObject> qbertObject);
	virtual ~EnemyObserver() = default;
	void Notify(dae::GameObject* object, Event e) override;

private:
	std::shared_ptr<dae::GameObject> m_QBert;
};

