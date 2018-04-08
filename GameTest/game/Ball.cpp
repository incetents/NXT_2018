
#include "stdafx.h"

#include "Ball.h"

#include "../App/SimpleLogger.h"
#include "../GameObject/Renderer.h"
#include "../Math/SimpleShapes.h"
#include "../Collision/Rigidbody.h"
#include "../Collision/Circle.h"

Ball::Ball(std::string _name, float scale, Vector2 position, Vector2 velocity) : GameObject(_name)
{
	// Set Shape
	GetComponent<Renderer>()->setVertexArray(SimpleShapes.v_circle);

	// Components
	AddComponent(new Rigidbody2D(transform));
	AddComponent(new CircleCollider2D(transform));

	// Data
	GetComponent<Transform>()->setPosition(position);
	GetComponent<Transform>()->setScale(scale);
	GetComponent<Rigidbody2D>()->setVelocity(velocity);
}