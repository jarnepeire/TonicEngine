#pragma once
#include "HexJumpAIComponent.h"

class UggWrongwayComponent final : public HexJumpAIComponent
{
public:
	enum class UggWrongway
	{
		Ugg,
		Wrongway
	};

	UggWrongwayComponent(UggWrongway type, unsigned int jumpSoundId);
	virtual ~UggWrongwayComponent() = default;

protected:
	UggWrongway m_UggWrongway;
	HexCoordinate DetermineNextJump() override;
};
