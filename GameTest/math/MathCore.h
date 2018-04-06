#pragma once

#include <math.h>
#include <cmath>
#include <cfloat>
#include <windows.h>
#include <string>
#include <vector>
#include <assert.h>

#include "Rotation.h"
#include "Random.h"

enum class Axis
{
	X,
	Y,
	Z
};

// Matrix Macros
#define MATRIX_INVERSE_EPSILON	1e-14f
#define MATRIX_EPSILON			1e-6f

#define Matrix2x2_Length 2
#define Matrix3x3_Length 3
#define Matrix4x4_Length 4

#define Matrix2x2_Size 4
#define Matrix3x3_Size 9
#define Matrix4x4_Size 16

// Math Macros
#define PI (std::atanf(1.0f) * 4.0f)
#define TWO_PI (2.0f*PI)
#define HALF_PI (0.5f*PI)
#define EULERS_E 2.71828182845904523536f
#define SQRT_TWO 1.41421356237309504880f
#define SQRT_THREE 1.73205080756887729352f
#define SQRT_1OVER2 0.70710678118654752440f
#define SQRT_1OVER3 0.57735026918962576450f
#define SQRT_TWO_INV 0.70710678118654752440f
#define SEC_TO_MS 1000.0f
#define MS_TO_SEC 0.001f
#define MAX_FLOAT 1e30f
#define FLOAT_EPSILON 1.192092896e-07f
#define DOUBLE_EPSILON 1.192092896e-07

// Macro Rotation Data
#define Rad_To_Deg(x) (x * (180.0f / PI))
#define Deg_To_Rad(x) (x * (PI / 180.0f))

// Macro Functions
#define MacroMax(a,b) (((a) > (b)) ? (a) : (b))
#define MacroMin(a,b) (((a) < (b)) ? (a) : (b))
#define MacroRound(x) (std::ceilf(value * (float)std::pow(10, x)) / (float)pow(10, x))
#define MacroClamp(n,_min,_max) MacroMax(_min, MacroMin(n, _max))
#define MacroLerp(a,b,t) a * (1.0f - t) + b * t
#define MacroBiLerp(a1,a2,b1,b2,t) (MacroLerp((MacroLerp(a1, a2, t)), (MacroLerp(b1, b2, t)), t))
#define MacroTriLerp(a1,a2,b1,b2,c1,c2,d1,d2,t) (MacroLerp((MacroBiLerp(a1, a2, b1, b2, t)), (MacroBiLerp(c1, c2, d1, d2, t)), t))
#define MacroHermite(A,B,C,D,t) (-A * 0.5f + (3.0f*B) * 0.5f - (3.0f*C) * 0.5f + D * 0.5f)*t*t*t + (A - (5.0f*B) * 0.5f + 2.0f*C - D * 0.5f)*t*t + (-A * 0.5f + C * 0.5f)*t + B

namespace MathCore
{
	template<typename T>
	static bool Compare(T a, T b)
	{
		return (a == b);
	}
	template<>
	static bool Compare(float a, float b)
	{
		return (abs(a - b) < FLOAT_EPSILON);
	}
	template<>
	static bool Compare(double a, double b)
	{
		return (abs(a - b) < DOUBLE_EPSILON);
	}

	template<typename T>
	static T Round(T value, u_int decimals)
	{
		return std::ceilf(value * (float)std::pow(10, decimals)) / (float)std::pow(10, decimals);
	}

	template<typename T>
	static void Swap(T& a, T& b)
	{
		T c = a;
		a = b;
		b = c;
	}

	template<typename T>
	static T InverseSqrt(T value)
	{
		if (value == 0) return 0;
		long i;
		float x2, y;

		x2 = value * 0.5F;
		y = value;
		i = *(long *)&y;
		i = 0x5f3759df - (i >> 1);
		y = *(float *)&i;
		y = y * (1.5f - (x2 * y * y));   // 1st iteration

		return  y;
	}

	template<typename T>
	static T Lerp(T a, T b, float t)
	{
		return a * (1.0f - t) + b * t;
	}

	template<typename T>
	static T To_Radians(T value)
	{
		return Deg_To_Rad(value);
	}

	template<typename T>
	static T To_Degrees(T value)
	{
		return Rad_To_Deg(value);
	}
}