#pragma once

#include "../GameObject/GameObject.h"
#include "../Math/Vector2.h"
#include <string>

class Bouncer : public GameObject
{
public:
	Bouncer(
		std::string _name = "",
		float scale = 50.0f,
		Vector2 position = Vector2(0, 0)
	);
};