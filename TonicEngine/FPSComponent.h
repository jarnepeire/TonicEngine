#pragma once
#include "Component.h"

namespace Tonic
{
	class Font;
	class GameObject;
	class TextComponent;

	class FPSComponent final : public Component
	{
	public:
		/* Doesn't create new text component, but sets a pointer to an already existing one */
		FPSComponent(const std::shared_ptr<TextComponent>& pTextComp);

		/* Adds a new text component using the given font, and sets a pointer to that text component */
		FPSComponent(const std::shared_ptr<Tonic::Font>& font);
		virtual ~FPSComponent() = default;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;


		void Initialize() override {}
		void PostInitialize() override {}
		void FixedUpdate(float dt) override;
		void Update(float dt) override;
		void Render() override {}

		/* Returns amount of frames per seconds */
		int GetFPS() const { return m_FPS; }

		/* Set value to display the FPS amount or not */
		void DisplayFPS(bool enable) { m_DisplayFPS = enable; }

	private:
		std::shared_ptr<TextComponent> m_pTextComponent;
		bool m_DisplayFPS;
		int m_Frames;
		int m_FPS;
		float m_TotalTime;

	};
}