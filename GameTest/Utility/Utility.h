#pragma once

namespace Utility
{
	template<typename T>
	void ClearArray(T* array_start, int length)
	{
		memset(array_start, 0, length);
	}

	template<typename T>
	void CopyrArray(T* array_src, T* array_dst, int length)
	{
		memcpy(array_dst, array_src, sizeof(T) * length);
	}
}