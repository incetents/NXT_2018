#pragma once

class Color3F
{
public:

	float r, g, b;

	Color3F()
	{
		r = g = b = 0;
	}
	Color3F(float _a)
	{
		r = g = b = _a;
	}
	Color3F(float _r, float _g, float _b) : r(_r), g(_g), b(_b)
	{

	}
};

// Default Colors
namespace Color
{
	extern const Color3F WHITE;
	extern const Color3F BLACK;
	extern const Color3F RED;
	extern const Color3F GREEN;
	extern const Color3F YELLOW;
	extern const Color3F BLUE;
	extern const Color3F ORANGE;
	extern const Color3F PURPLE;
	extern const Color3F CYAN;
}