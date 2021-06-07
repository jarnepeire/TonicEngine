#pragma once
#include <Observer.h>
#include <memory>
#include <string>

class HealthComponent;
class HexGrid;
class EndGameObserver : public Tonic::Observer
{
public:
	//To create link it to an existing health component
	EndGameObserver(const std::string& endGameSceneName, unsigned int endGameSoundId);

	virtual ~EndGameObserver() = default;
	void Notify(Tonic::GameObject * object, int eventId) override;

private:
	std::string m_EndGameSceneName;
	unsigned int m_EndGameSoundID;
};

