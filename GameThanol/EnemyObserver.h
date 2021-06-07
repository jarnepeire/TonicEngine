#pragma once
#include <Observer.h>
#include <memory>

class EnemyObserver : public Tonic::Observer
{
public:
	EnemyObserver(std::shared_ptr<Tonic::GameObject> qbertObject);
	virtual ~EnemyObserver() = default;
	void Notify(Tonic::GameObject* object, int eventId) override;

private:
	std::weak_ptr<Tonic::GameObject> m_QBert;
};

