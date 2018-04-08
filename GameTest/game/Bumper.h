#pragma once

#include "../GameObject/GameObject.h"
#include "../App/SimpleLogger.h"
#include "../Math/SimpleShapes.h"

class Bumper : public GameObject
{
private:

public:
	Bumper(
		std::string _name = "",
		Vector2 position = Vector2(0, 0),
		Vector2 size = Vector2(1, 1)
	);

};