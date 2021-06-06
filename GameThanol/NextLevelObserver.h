#pragma once
#include <Observer.h>
#include <string>
#include <memory>

class HexGrid;
class NextLevelObserver : public Observer
{
public:
	NextLevelObserver(std::shared_ptr<HexGrid> currentLevelGrid, const std::string& nextLevelName);
	virtual ~NextLevelObserver() = default;
	void Notify(dae::GameObject * object, Event e) override;

private:
	std::weak_ptr<HexGrid> m_pGrid;
	std::string m_NextLevelName;
};

