#pragma once
#include <Observer.h>
#include <memory>

namespace dae
{
	class GameObject;
}

class HexGrid;
class QBertObserver : public Observer
{
public:
	QBertObserver(std::shared_ptr<HexGrid> currentLevelGrid, std::shared_ptr<dae::GameObject> pQbertObj);
	virtual ~QBertObserver() = default;
	void Notify(dae::GameObject * object, Event e) override;

private:
	std::weak_ptr<HexGrid> m_pGrid;
	std::weak_ptr<dae::GameObject> m_pQBert;
};

