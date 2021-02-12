#pragma once
#include "Component.h"

namespace dae
{
	class Texture2D;
}

class ImageComponent : public Component
{
public:
	ImageComponent(dae::GameObject* parent, const std::string& filename);

	void Update(float dt) override;
	void Render() override;

	void SetTexture(const std::string& filename);

private:
	std::shared_ptr<dae::Texture2D> m_Texture{};

};

