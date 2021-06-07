#pragma once
#include "Component.h"
#include <string>

namespace Tonic
{
	class Texture2D;
	class GameObject;


	class ImageComponent : public Component
	{
	public:
		ImageComponent(Tonic::GameObject* parent, const std::string& filename, float scale = 1.f);

		void Initialize() override;
		void PostInitialize() override;
		void FixedUpdate(float dt) override;
		void Update(float dt) override;
		void Render() override;

		float GetImageWidth() const { return m_ImageWidth; }
		float GetImageHeight() const { return m_ImageHeight; }

		void SetTexture(const std::string& filename);
		Tonic::Texture2D* GetTexture() const { return m_Texture.get(); }
		void CanRender(bool b) { m_CanRender = b; }

	private:
		bool m_CanRender;
		std::shared_ptr<Tonic::Texture2D> m_Texture{};
		float m_ImageWidth;
		float m_ImageHeight;
		float m_Scale;


	};

}