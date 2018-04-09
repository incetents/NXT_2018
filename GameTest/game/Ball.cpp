
#include "stdafx.h"

#include "Ball.h"

#include "../App/SimpleLogger.h"
#include "../GameObject/Renderer.h"
#include "../Math/SimpleShapes.h"
#include "../Collision/Rigidbody.h"
#include "../Collision/Circle.h"
#include "Flipper.h"

Ball::Ball(std::string _name, float scale, Vector2 position, Vector2 velocity) : GameObject(_name)
{
	// Create child
	cube_effect = new GameObject(SimpleShapes.v_cube, _name + "-effect");
	cube_effect->transform->setParent(transform);
	cube_effect->transform->setScale(0.3f);

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

void Ball::OnCollide(Collider c)
{
#if _DEBUG
	SimpleLogger.Print(c.getGameObjectReference()->name);
#endif

	// Check for flippers
	if (
		c.getGameObjectReference()->name == "FlipperPiece"
		)
	{

		// Upcast to get flipper object
		Flipper* F = dynamic_cast<Flipper*>(c.getGameObjectReference()->transform->getParent()->getGameObjectReference());
		// Check energy
		float energy = F->getEnergy();
		energy = sqrt(energy); // sqrt for curve effect
		float strength = F->getStrength();
		Vec2 aim = (F->getFlipperNormal() + Vec2(0, 1)).Normalize();

		//SimpleLogger.ErrorStatic("ENG: " + toString(energy));

		// Move Upwards
		GetComponent<Transform>()->increasePosition(Vec3(0, 20, 0) * energy);

		// Add Force
		GetComponent<Rigidbody2D>()->addForce(aim * energy * strength);
	}
}
void Ball::OnTrigger(Collider c)
{
	SimpleLogger.Print("TRIGGER");
}
void Ball::Update(float delta)
{
	// Call gameobject update
	GameObject::Update(delta);

	cube_effect->transform->increaseRotation(Vec3(2, 2, 0));
}