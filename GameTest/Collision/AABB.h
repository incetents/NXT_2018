#pragma once

#include "../Math/Vector2.h"
#include "../GameObject/Component.h"
#include "Collider.h"

class AABBCollider2D : public Component, public Collider
{
private:
	// Edge points of aabb collider
	Vector2 m_min;
	Vector2 m_max;

public:

	
};