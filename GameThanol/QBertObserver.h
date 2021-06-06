#pragma once
#include <Observer.h>
#include <memory>

class HexGrid;
class QBertObserver : public Observer
{
public:
	QBertObserver(std::shared_ptr<HexGrid> currentLevelGrid);
	virtual ~QBertObserver() = default;
	void Notify(dae::GameObject * object, Event e) override;

private:
	std::shared_ptr<HexGrid> m_pGrid;
};

