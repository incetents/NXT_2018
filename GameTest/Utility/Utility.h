#pragma once

#include <vector>

#define toString(x) std::to_string(x)

namespace Utility
{
	template<typename T>
	void ClearArray(T* array_start, int length)
	{
		memset(array_start, 0, length);
	}

	template<typename T>
	void CopyArray(T* array_src, T* array_dst, int length)
	{
		memcpy(array_dst, array_src, sizeof(T) * length);
	}

	template<typename T>
	void EraseVectorByValue(std::vector<T>& vector, T value)
	{
		vector.erase(std::remove(vector.begin(), vector.end(), value), vector.end());
	}

	// Referenced from
	// https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
	template <typename T>
	int Sign(T val) { return (T(0) < val) - (val < T(0)); }
}

namespace Random
{
	// Returns random float from 0 to 1
	float Float01();
	// Return random float from -1 to +1
	float FloatN1();
	// Return random float from min to max
	float Float(float min, float max);
}