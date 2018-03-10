#pragma once

enum ColorIndex
{
	WHITE,
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	ORANGE,
	PURPLE,
	CYAN,
	TOTAL
};

class Color3F
{
private:
	static Color3F DefaultColors[];
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

	// Retrieve Basic Colors
	static Color3F getColor(ColorIndex c);
};

