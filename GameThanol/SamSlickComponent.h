#pragma once
#include "HexJumpAIComponent.h"

class SamSlickComponent : public HexJumpAIComponent
{
public:
	SamSlickComponent(Tonic::GameObject* parent, unsigned int jumpSoundId);
	virtual ~SamSlickComponent() = default;

protected:
	HexCoordinate DetermineNextJump() override;
};

