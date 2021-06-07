#pragma once
#include <Observer.h>
#include <memory>
#include <string>

class HexGrid;
class SamSlickObserver : public Tonic::Observer
{
public:
	SamSlickObserver(std::shared_ptr<HexGrid> currentLevelGrid);
	virtual ~SamSlickObserver() = default;
	void Notify(Tonic::GameObject * object, int eventId) override;
private:
	std::weak_ptr<HexGrid> m_pGrid;
};

