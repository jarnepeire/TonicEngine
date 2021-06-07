#pragma once
#include <Observer.h>
#include <memory>

namespace Tonic
{
	class GameObject;
}

class HexGrid;
class QBertObserver : public Tonic::Observer
{
public:
	QBertObserver(std::shared_ptr<HexGrid> currentLevelGrid, std::shared_ptr<Tonic::GameObject> pQbertObj);
	virtual ~QBertObserver() = default;
	void Notify(Tonic::GameObject * object, int eventId) override;

private:
	std::weak_ptr<HexGrid> m_pGrid;
	std::weak_ptr<Tonic::GameObject> m_pQBert;
};

