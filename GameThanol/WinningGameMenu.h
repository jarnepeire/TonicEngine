#pragma once
#include <Scene.h>
class MenuButton;

class WinningGameMenu : public dae::Scene
{
public:
	WinningGameMenu(const std::string& name, int idx);

	void Initialize() override;
	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() const override;

private:
	std::shared_ptr<MenuButton> m_pToMainMenuButton;
	unsigned int m_ClickSoundID;
};

