#pragma once
#include <stdint.h>

namespace dae
{
	class BaseGameThanol
	{
	public:
		BaseGameThanol(uint32_t windowWidth = 640, uint32_t windowHeight = 480, float cappedFPS = 60.f);
		~BaseGameThanol() = default;
		BaseGameThanol(const BaseGameThanol& g) = delete;
		BaseGameThanol(BaseGameThanol&& g) = delete;
		BaseGameThanol& operator=(const BaseGameThanol& g) = delete;
		BaseGameThanol& operator=(BaseGameThanol&& g) = delete;

		virtual void CreateGameScenes() = 0;

		uint32_t GetWindowWidth() const { return m_WindowWidth; }
		uint32_t GetWindowHeight() const { return m_WindowHeight; }
		float GetCappedFPS() const { return m_CappedFPS; }

	private:
		uint32_t m_WindowWidth;
		uint32_t m_WindowHeight;
		float m_CappedFPS;
	};

}

