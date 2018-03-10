#include "stdafx.h"

#include "Color.h"

Color3F Color3F::DefaultColors[] =
{
	Color3F(1,1,1),
	Color3F(0,0,0),
	Color3F(230.f/255.f, 25.f/255.f, 75.f/255.f),
	Color3F(60.f/255.f, 180.f/255.f, 75.f/255.f),
	Color3F(1,1,25.f/255.f),
	Color3F(0, 130.f/255.f, 200.f/255.f),
	Color3F(245.f/255.f, 130.f/255.f, 48.f/255.f),
	Color3F(145.f/255.f, 30.f/255.f, 180.f/255.f),
	Color3F(70.f/255.f, 240.f/255.f, 240.f/255.f)
};

Color3F Color3F::getColor(ColorIndex c)
{
	return DefaultColors[(int)c];
}