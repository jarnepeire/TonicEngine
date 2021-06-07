#pragma once
#include <Scene.h>
class MenuButton;

class ControlsMenu : public Tonic::Scene
{
public:
	ControlsMenu(const std::string& name, int idx);
	virtual ~ControlsMenu() = default;

	void Initialize() override;
	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() const override;

private:
	std::shared_ptr<MenuButton> m_pToMainMenuButton;
	unsigned int m_ClickSoundID;
};

