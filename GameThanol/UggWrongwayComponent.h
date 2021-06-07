#pragma once
#include "HexJumpAIComponent.h"

class UggWrongwayComponent : public HexJumpAIComponent
{
public:
	enum class UggWrongway
	{
		Ugg,
		Wrongway
	};

	UggWrongwayComponent(dae::GameObject* parent, UggWrongway type, unsigned int jumpSoundId);
	virtual ~UggWrongwayComponent() = default;

protected:
	UggWrongway m_UggWrongway;
	HexCoordinate DetermineNextJump() override;
};
