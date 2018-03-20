#include "stdafx.h"

#include "Color.h"

const Color3F Color::WHITE	= Color3F(1, 1, 1);
const Color3F Color::BLACK	= Color3F(0, 0, 0);
const Color3F Color::RED	= Color3F(230.f / 255.f, 25.f / 255.f, 75.f / 255.f);
const Color3F Color::GREEN	= Color3F(60.f / 255.f, 180.f / 255.f, 75.f / 255.f);
const Color3F Color::BLUE	= Color3F(0, 130.f / 255.f, 200.f / 255.f);
const Color3F Color::YELLOW	= Color3F(1, 1, 25.f/255.f);
const Color3F Color::ORANGE	= Color3F(245.f / 255.f, 130.f / 255.f, 48.f / 255.f);
const Color3F Color::PURPLE	= Color3F(145.f / 255.f, 30.f / 255.f, 180.f / 255.f);
const Color3F Color::CYAN	= Color3F(70.f / 255.f, 240.f / 255.f, 240.f / 255.f);

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