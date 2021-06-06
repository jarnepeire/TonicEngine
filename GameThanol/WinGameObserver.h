#pragma once
#include <Observer.h>
#include <string>
#include <memory>

class HexGrid;
class WinGameObserver : public Observer
{
public:
	WinGameObserver(std::shared_ptr<HexGrid> currentLevelGrid, const std::string& winningSceneName);

	virtual ~WinGameObserver() = default;
	void Notify(dae::GameObject * object, Event e) override;

private:
	std::weak_ptr<HexGrid> m_pGrid;
	std::string m_WinningSceneName;
};

