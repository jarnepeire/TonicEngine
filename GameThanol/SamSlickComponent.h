#pragma once
#include "HexJumpAIComponent.h"

class SamSlickComponent : public HexJumpAIComponent
{
public:
	SamSlickComponent(dae::GameObject* parent);
	virtual ~SamSlickComponent() = default;

protected:
	HexCoordinate DetermineNextJump() override;
};

