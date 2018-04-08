#include "stdafx.h"

#include "Bumper.h"
#include "../Collision/OBB.h"

Bumper::Bumper(
	std::string _name,
	Side bumperSide,
	float restAngle,
	float hitAngle,
	Vector2 position,
	Vector2 size) : GameObject(_name), m_restAngle(restAngle), m_hitAngle(hitAngle)
{

	// Data of self
	GetComponent<Transform>()->setPosition(position);
	GetComponent<Transform>()->setScale(Vector3(size, 0));

	// Child
	bumperchild = new GameObject(_name + "-child");
	bumperchild->GetComponent<Transform>()->setParent(transform);

	// Add OBB
	bumperchild->AddComponent<>(new OBB2D(bumperchild->transform));

	// Set Shape
	bumperchild->GetComponent<Renderer>()->setVertexArray(SimpleShapes.v_box);

	// Set Offset
	if (bumperSide == Side::LEFT)
	{
		bumperchild->GetComponent<Transform>()->setPosition(Vec2(+0.5f, 0.0f));
	}
	else
	{
		bumperchild->GetComponent<Transform>()->setPosition(Vec2(-0.5f, 0.0f));
	}
		

	
}