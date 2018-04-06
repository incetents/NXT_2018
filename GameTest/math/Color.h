#pragma once

class Color3F
{
public:

	static constexpr  Color3F WHITE()	{ return Color3F(1, 1, 1); }
	static constexpr  Color3F BLACK()	{ return Color3F(0, 0, 0); }
	static constexpr  Color3F RED()		{ return Color3F(230.f / 255.f, 25.f / 255.f, 75.f / 255.f); }
	static constexpr  Color3F GREEN()	{ return Color3F(60.f / 255.f, 180.f / 255.f, 75.f / 255.f); }
	static constexpr  Color3F BLUE()	{ return Color3F(0, 130.f / 255.f, 200.f / 255.f); }
	static constexpr  Color3F YELLOW()	{ return Color3F(1, 1, 25.f / 255.f);}
	static constexpr  Color3F ORANGE()	{ return Color3F(245.f / 255.f, 130.f / 255.f, 48.f / 255.f);}
	static constexpr  Color3F PURPLE()	{ return Color3F(145.f / 255.f, 30.f / 255.f, 180.f / 255.f);}
	static constexpr  Color3F CYAN()	{ return Color3F(70.f / 255.f, 240.f / 255.f, 240.f / 255.f);}

	constexpr Color3F(float r, float g, float b)
		: r(r), g(g), b(b)
	{}
	constexpr Color3F()
		: r(0), g(0), b(0)
	{}
	constexpr Color3F(float a)
		: r(a), g(a), b(a)
	{}

	float r, g, b;

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