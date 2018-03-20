
#include "stdafx.h"

#include <random>
#include "Utility.h"

namespace Random
{
	float Float01()
	{
		return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	}
	float FloatN1()
	{
		return Float01() * 2.0f - 1.0f;
	}
	float Float(float min, float max)
	{
		return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	}
}