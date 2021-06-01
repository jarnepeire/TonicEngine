#pragma once
#include <glm/glm.hpp>

inline float FLerp(float value1, float value2, float alpha)
{
    return value1 + alpha * (value2 - value1);
}

inline glm::vec2 Vec2ParabolaLerp(glm::vec2& startPos, glm::vec2& endPos, float a, float b, float c, float alpha)
{
    float x = (1 - alpha) * startPos.x + alpha * endPos.x;
    float y = a * (x * x) + b * x + c;
    return glm::vec2(x, y);
}

template <typename T>
inline void Clamp(T& value, T min, T max)
{
    if (value < min)
        value = min;

	if (value > max)
		value = max;
}