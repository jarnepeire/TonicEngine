#pragma once
#include <BaseGameThanol.h>

class QBertGame final : public dae::BaseGameThanol
{
public:
	QBertGame(uint32_t windowWidth = 640, uint32_t windowHeight = 480, float cappedFPS = 60.f);
	~QBertGame() = default;

	void CreateGameScenes() override;
};

