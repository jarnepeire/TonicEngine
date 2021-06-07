#pragma once
#include <BaseGameThanol.h>
#include "Singleton.h"

class QBertGame final : public Tonic::BaseGameThanol, public Tonic::Singleton<QBertGame>
{
public:
	QBertGame(uint32_t windowWidth = 640, uint32_t windowHeight = 480, float cappedFPS = 60.f);
	~QBertGame() = default;

	void CreateGameScenes() override;
};

