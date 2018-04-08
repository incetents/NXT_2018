#pragma once

#include "../GameObject/GameObject.h"
#include "../Math/Vector2.h"
#include <string>

class Wall : public GameObject
{
	Vector2 point1;
	Vector2 point2;
public:
	Wall(
		std::string _name = "",
		Vector2 position1 = Vector2(0, 0),
		Vector2 position2 = Vector2(0, 0),
		Color3F color1 = Color3F::RED(),
		Color3F color2 = Color3F::BLUE()
	);
	
	void UpdatePoint1(Vec2 p1);
	void UpdatePoint2(Vec2 p2);
	void UpdatePoints(Vec2 p1, Vec2 p2);
};