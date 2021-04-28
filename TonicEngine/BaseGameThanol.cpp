#include "TonicEnginePCH.h"
#include "BaseGameThanol.h"

dae::BaseGameThanol::BaseGameThanol(uint32_t windowWidth, uint32_t windowHeight, float cappedFPS)
	: m_WindowWidth(windowWidth)
	, m_WindowHeight(windowHeight)
	, m_CappedFPS(cappedFPS)
{
}
