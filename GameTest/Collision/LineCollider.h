#pragma once

#include "../GameObject/Component.h"
#include "../Math/Vector2.h"
#include "Collider.h"

class LineCollider2D : public Component, public Collider
{
	friend class Vector2;
	friend class GameObject;
	friend class Transform;
protected:

	// Data
	Vector2 m_p1;
	Vector2 m_p2;
public:
	LineCollider2D(Transform* T);

	

	// Set Points
	void setPoint1(Vector2 v);
	void setPoint2(Vector2 v);
	void setPoints(Vector2 v1, Vector2 v2);

	// Get Points
	Vector2 getPoint1() const;
	Vector2 getPoint2() const;

	// Get Data
	Vector2 getDirection() const;
	Vector2 getNormal() const;




};