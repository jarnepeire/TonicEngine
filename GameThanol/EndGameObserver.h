#pragma once
#include <Observer.h>
#include <memory>
#include <string>

class HealthComponent;
class HexGrid;
class EndGameObserver : public Observer
{
public:
	//To create link it to an existing health component
	EndGameObserver(const std::string& endGameSceneName);

	virtual ~EndGameObserver() = default;
	void Notify(dae::GameObject * object, Event e) override;

private:
	std::string m_EndGameSceneName;
};

