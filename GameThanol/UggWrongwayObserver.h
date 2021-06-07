#pragma once
#include <Observer.h>
#include <memory>
#include <string>
class HexGrid;

class UggWrongwayObserver : public Tonic::Observer
{
public:
	UggWrongwayObserver(std::shared_ptr<HexGrid> currentLevelGrid);
	virtual ~UggWrongwayObserver() = default;
	void Notify(Tonic::GameObject * object, int eventId) override;

private:
	std::weak_ptr<HexGrid> m_pGrid;
};

