#pragma once
#include <Observer.h>
#include <memory>
#include <string>
class HexGrid;
class SamSlickObserver : public Observer
{
public:
	SamSlickObserver(std::shared_ptr<HexGrid> currentLevelGrid);
	virtual ~SamSlickObserver() = default;
	void Notify(dae::GameObject * object, Event e) override;
private:
	std::shared_ptr<HexGrid> m_pGrid;
};

