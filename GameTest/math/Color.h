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

	static Color3F lerp(Color3F start, Color3F end, float t)
	{
		return (start * (1.0f - t) + end * t);
	}

	// Overloads
	Color3F operator+(const Color3F& c) const;
	Color3F operator-(const Color3F& c) const;
	Color3F operator*(const Color3F& c) const;
	Color3F operator/(const Color3F& c) const;

	Color3F operator+(const float t) const;
	Color3F operator-(const float t) const;
	Color3F operator*(const float t) const;
	Color3F operator/(const float t) const;
	
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