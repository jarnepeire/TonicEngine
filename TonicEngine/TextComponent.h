#pragma once
#include "Transform.h"
#include "Component.h"

namespace dae 
{
	class Font;
	class Texture2D;
	class GameObject;
}

class TextComponent : public Component
{
public:
	TextComponent(dae::GameObject* parent, const std::string& text = "", const std::shared_ptr<dae::Font>& font = nullptr);
	virtual ~TextComponent() = default;

	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	void SetText(const std::string& text);

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<dae::Font> m_Font;
	std::shared_ptr<dae::Texture2D> m_Texture;
};

