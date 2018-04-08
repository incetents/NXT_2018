
#include "stdafx.h"

#include "Bouncer.h"

#include "../App/SimpleLogger.h"
#include "../GameObject/Renderer.h"
#include "../Math/SimpleShapes.h"
#include "../Collision/Rigidbody.h"
#include "../Collision/Circle.h"

Bouncer::Bouncer(std::string _name, float scale, Vector2 position) : GameObject(_name)
{
	// Set Shape
	GetComponent<Renderer>()->setVertexArray(SimpleShapes.v_circle);

	// Components
	AddComponent(new CircleCollider2D(transform));

	// Data
	GetComponent<Transform>()->setPosition(position);
	GetComponent<Transform>()->setScale(scale);
}