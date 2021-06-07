#pragma once
#include <Scene.h>
class MenuButton;
namespace Tonic
{
	class GameObject;
}
class WinningGameMenu : public Tonic::Scene
{
public:
	WinningGameMenu(const std::string& name, int idx);

	void Initialize() override;
	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() const override;

	void SetFinalScore(int score);
private:
	std::shared_ptr<MenuButton> m_pToMainMenuButton;
	std::shared_ptr<Tonic::GameObject> m_pFinalScoreObj;
	unsigned int m_ClickSoundID;
};

