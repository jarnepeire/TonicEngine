#pragma once
#include <Observer.h>
#include <string>

class WinGameObserver : public Observer
{
public:
	WinGameObserver(const std::string& winningSceneName);

	virtual ~WinGameObserver() = default;
	void Notify(dae::GameObject * object, Event e) override;

private:
	std::string m_WinningSceneName;
};

