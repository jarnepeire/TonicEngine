#pragma once
#include <Observer.h>
#include <string>
#include <memory>

class HexGrid;
class NextLevelObserver : public Tonic::Observer
{
public:
	NextLevelObserver(std::shared_ptr<HexGrid> currentLevelGrid, const std::string& nextLevelName, unsigned int nextLevelSoundId);
	virtual ~NextLevelObserver() = default;
	void Notify(Tonic::GameObject * object, int eventId) override;

private:
	std::weak_ptr<HexGrid> m_pGrid;
	std::string m_NextLevelName;
	unsigned int m_NextLevelSoundID;
};

