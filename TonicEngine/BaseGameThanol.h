#pragma once
#include <stdint.h>

namespace Tonic
{
	class BaseGameThanol
	{
	public:
		BaseGameThanol(uint32_t windowWidth = 640, uint32_t windowHeight = 480, float cappedFPS = 60.f);
		~BaseGameThanol() = default;

		BaseGameThanol(const BaseGameThanol& other) = delete;
		BaseGameThanol(BaseGameThanol&& other) = delete;
		BaseGameThanol& operator=(const BaseGameThanol& other) = delete;
		BaseGameThanol& operator=(BaseGameThanol&& other) = delete;

		/* Creates the game scenes that define the game */
		virtual void CreateGameScenes() = 0;

		/* Returns width of the game window */
		uint32_t GetWindowWidth() const { return m_WindowWidth; }

		/* Returns height of the game window */
		uint32_t GetWindowHeight() const { return m_WindowHeight; }

		/* Returns amount of capped frames per second of the game window */
		float GetCappedFPS() const { return m_CappedFPS; }

	private:
		uint32_t m_WindowWidth;
		uint32_t m_WindowHeight;
		float m_CappedFPS;
	};

}

