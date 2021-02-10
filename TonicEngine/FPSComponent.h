#pragma once
#include "Component.h"

namespace dae
{
	class Font;
	class GameObject;
}
class TextComponent;

class FPSComponent : public Component
{
public:
	FPSComponent(dae::GameObject* parent, const std::shared_ptr<dae::Font>& font = nullptr);
	virtual ~FPSComponent() = default;

	void Update(float dt) override;
	void Render() override;

	int GetFPS() const { return m_FPS; }
	void DisplayFPS(bool enable) { m_DisplayFPS = enable; }
private:
	bool m_DisplayFPS;
	std::shared_ptr<TextComponent> m_pTextComponent = nullptr;

	int m_Frames;
	int m_FPS;
	float m_TotalTime;
	
};
