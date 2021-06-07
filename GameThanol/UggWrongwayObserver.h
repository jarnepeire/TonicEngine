#pragma once
#include <Observer.h>
#include <memory>
#include <string>
class HexGrid;

class UggWrongwayObserver : public Observer
{
public:
	UggWrongwayObserver(std::shared_ptr<HexGrid> currentLevelGrid);
	virtual ~UggWrongwayObserver() = default;
	void Notify(dae::GameObject * object, Event e) override;

private:
	std::weak_ptr<HexGrid> m_pGrid;
};

