#pragma once
#include <Observer.h>
#include <string>
#include <memory>

class HexGrid;
class WinGameObserver : public Tonic::Observer
{
public:
	WinGameObserver(std::shared_ptr<HexGrid> currentLevelGrid, const std::string& winningSceneName, unsigned int winGameSoundId);
	virtual ~WinGameObserver() = default;
	void Notify(Tonic::GameObject * object, int eventId) override;

private:
	std::weak_ptr<HexGrid> m_pGrid;
	std::string m_WinningSceneName;
	unsigned int m_WinGameSoundID;
};

