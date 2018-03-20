#pragma once

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