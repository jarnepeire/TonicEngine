#pragma once
#include <Scene.h>

class MenuButton;

class MainMenu : public dae::Scene
{
public:
	MainMenu(const std::string& name, int idx);

	void Initialize() override;
	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() const override;

private:
	std::shared_ptr<MenuButton> m_pOnePlayerButton;
	std::shared_ptr<MenuButton> m_pTwoPlayerButton;
	std::shared_ptr<MenuButton> m_pVersusButton;

	unsigned int m_ClickSoundID;
};

