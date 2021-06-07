#pragma once
#include "Component.h"
#include <string>

namespace Tonic
{
	class Texture2D;
	class GameObject;

	class ImageComponent final : public Component
	{
	public:
		ImageComponent(const std::string& filename, float scale = 1.f);
		virtual ~ImageComponent() = default;

		ImageComponent(const ImageComponent& other) = delete;
		ImageComponent(ImageComponent&& other) = delete;
		ImageComponent& operator=(const ImageComponent& other) = delete;
		ImageComponent& operator=(ImageComponent&& other) = delete;

		void Initialize() override;
		void PostInitialize() override {}
		void FixedUpdate(float) override {}
		void Update(float) override {}
		void Render() override;

		/* Returns the width of the image */
		float GetImageWidth() const { return m_ImageWidth; }

		/* Returns the height of the image */
		float GetImageHeight() const { return m_ImageHeight; }

		/* Set image to a new texture */
		void SetTexture(const std::string& filename);

		/* Returns raw pointer of the texture */
		Tonic::Texture2D* GetTexture() const { return m_pTexture.get(); }
		
		/* Set value of whether the image can be rendered or not */
		void CanRender(bool b) { m_CanRender = b; }

	private:
		bool m_CanRender;
		std::shared_ptr<Tonic::Texture2D> m_pTexture{};
		float m_ImageWidth;
		float m_ImageHeight;
		float m_Scale;
	};
}