#pragma once
#include <cmath>

namespace kiko
{
	constexpr float pi = 3.141592653589793238462643f;
	constexpr float twopi = 3.141592653589793238462643f * 2.0f;
	constexpr float halfpi = 3.141592653589793238462643f / 2.0f;

	constexpr float RadiansToDegrees(float radians) { return radians * 180.0f / pi; }
	constexpr float DegreesToRadians(float degrees) { return degrees * pi / 180.0f; }

	constexpr int Wrap(int value, int max)
	{
		return (value % max) + ((value < 0) ? max : 0);
	}
	
	inline float Wrap(float value, float max)
	{
		return std::fmod(value, max) + ((value < 0) ? max : 0);
	}

	template <typename T>
	inline T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}
	
	template <typename T>
	inline T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template <typename T>
	inline T Clamp(T value, T min, T max)
	{
		if (min > max) std::swap(min, max);

		return (value < min) ? min : (value > max) ? max : value;
	} 
}