#include "stdafx.h"

#include "Color.h"

// Overloads
Color3F Color3F::operator+(const Color3F& c) const
{
	Color3F m;
	m.r = r + c.r;
	m.g = g + c.g;
	m.b = b + c.b;
	return m;
}
Color3F Color3F::operator-(const Color3F& c) const
{
	Color3F m;
	m.r = r - c.r;
	m.g = g - c.g;
	m.b = b - c.b;
	return m;
}
Color3F Color3F::operator*(const Color3F& c) const
{
	Color3F m;
	m.r = r * c.r;
	m.g = g * c.g;
	m.b = b * c.b;
	return m;
}
Color3F Color3F::operator/(const Color3F& c) const
{
	Color3F m;
	m.r = r / c.r;
	m.g = g / c.g;
	m.b = b / c.b;
	return m;
}

Color3F Color3F::operator+(const float t) const
{
	Color3F m;
	m.r = r + t;
	m.g = g + t;
	m.b = b + t;
	return m;
}
Color3F Color3F::operator-(const float t) const
{
	Color3F m;
	m.r = r - t;
	m.g = g - t;
	m.b = b - t;
	return m;
}
Color3F Color3F::operator*(const float t) const
{
	Color3F m;
	m.r = r * t;
	m.g = g * t;
	m.b = b * t;
	return m;
}
Color3F Color3F::operator/(const float t) const
{
	Color3F m;
	m.r = r / t;
	m.g = g / t;
	m.b = b / t;
	return m;
}