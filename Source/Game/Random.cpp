#include "stdafx.h"
#include "Random.hpp"


namespace Utils
{
	const float RandomFloat(const float& aMin, const float& aMax)
	{
		std::random_device device;
		std::mt19937 randomGenerator{ device() };

		std::uniform_int_distribution<int> uid(0, 10000);
		return aMin + (aMax - aMin) * (static_cast<float>(uid(randomGenerator)) / 10000.0f);
	}

	const int RandomInt(const int& aMin, const int& aMax)
	{
		std::random_device device;
		std::mt19937 randomGenerator{ device() };

		std::uniform_int_distribution<int> uid(aMin, aMax);
		return uid(randomGenerator);
	}
}