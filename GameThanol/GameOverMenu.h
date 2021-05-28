#pragma once
#include <Scene.h>

class GameOverMenu : public dae::Scene
{
public:
	GameOverMenu(const std::string& name, int idx);

	void Initialize() override;
	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() const override;
};

