#pragma once
#include "HexJumpAIComponent.h"

class SamSlickComponent final : public HexJumpAIComponent
{
public:
	SamSlickComponent(unsigned int jumpSoundId);
	virtual ~SamSlickComponent() = default;

protected:
	HexCoordinate DetermineNextJump() override;
};

