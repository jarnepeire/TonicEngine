#pragma once
#include <BaseGameThanol.h>

class QBertGame final : public dae::BaseGameThanol
{
public:
	QBertGame() = default;
	~QBertGame() = default;

	void CreateGameScenes() override;
};

