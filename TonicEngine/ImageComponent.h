#pragma once
#include "Component.h"

namespace dae
{
	class Texture2D;
}

class ImageComponent : public Component
{
public:
	ImageComponent(dae::GameObject* parent, const std::string& filename, float scale = 1.f);

	void FixedUpdate(float dt) override;
	void Update(float dt) override;
	void Render() override;

	float GetImageWidth() const { return m_ImageWidth; }
	float GetImageHeight() const { return m_ImageHeight; }

	void SetTexture(const std::string& filename);
	dae::Texture2D* GetTexture() const { return m_Texture.get(); }
	void CanRender(bool b) { m_CanRender = b; }

private:
	bool m_CanRender;
	std::shared_ptr<dae::Texture2D> m_Texture{};
	float m_ImageWidth;
	float m_ImageHeight;
	float m_Scale;
	

};

