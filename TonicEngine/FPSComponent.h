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
	//Doesn't create new text component, but sets a pointer to an already existing one
	FPSComponent(dae::GameObject* parent, const std::shared_ptr<TextComponent>& pTextComp);

	//Adds a new text component using the given font, and sets a pointer to that text component
	FPSComponent(dae::GameObject* parent, const std::shared_ptr<dae::Font>& font);
	virtual ~FPSComponent() = default;

	void Initialize() override;
	void PostInitialize() override;
	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	int GetFPS() const { return m_FPS; }
	void DisplayFPS(bool enable) { m_DisplayFPS = enable; }
private:
	std::shared_ptr<TextComponent> m_pTextComponent;
	bool m_DisplayFPS;

	int m_Frames;
	int m_FPS;
	float m_TotalTime;
	
};
