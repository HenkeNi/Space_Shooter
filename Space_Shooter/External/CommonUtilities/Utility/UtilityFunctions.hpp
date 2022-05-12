#pragma once
#include <cassert>
#include <random>


namespace CommonUtilities
{
	template <typename T>
	T Min(T aValue1, T aValue2)
	{
		T min = aValue1 < aValue2 ? aValue1 : aValue2;
		return min;
	}

	template <typename T>
	T Max(T aValue1, T aValue2)
	{
		T max = aValue1 > aValue2 ? aValue1 : aValue2;
		return max;
	}

	template <typename T>
	T Abs(T anArg)
	{
		T value = anArg < 0 ? anArg * (-1) : anArg;
		return value;
	}

	template <typename T>
	T Clamp(T aValue, T aMin, T aMax)
	{
		assert(aMax >= aMin);
		return std::max(aMin, std::min(aMax, aValue));
	}

	template <typename T>
	T Lerp(T a, T b, float c)
	{
		T result = (a + c * (b - a));
		return result;
	}

	template <typename T>
	void Swap(T& aValue1, T& aValue2)
	{
		T temp = aValue1;
		aValue1 = aValue2;
		aValue2 = temp;
	}

	template <typename T> // TODO: FIX!!!
	T GetRandomNumber(T aMin, T aMax)
	{
		static std::random_device seed;
		static std::mt19937 randomEngine(seed());

		std::uniform_int_distribution<T> randomDist(aMin, aMax);
		return randomDist(randomEngine);
	}
}