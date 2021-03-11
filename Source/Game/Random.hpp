#pragma once
#include <Random>

namespace Utils
{
	const float RandomFloat(const float& aMin, const float& aMax)
	{
		std::random_device device;
		std::mt19937 randomGenerator{ device() };

		std::uniform_int_distribution<int> uid(0, 10000);
		return aMin + (aMax - aMin) * (static_cast<float>(uid(randomGenerator)) / 10000.0f);
	}
}