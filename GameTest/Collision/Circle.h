#pragma once

#include "../GameObject/Component.h"

class CircleCollider2D : public Component
{
	friend class Vector2;
	friend class GameObject;
	friend class Transform;
	friend class Rigidbody2D;
	friend class LineCollider2D;

private:
	// Object References
	GameObject* m_gameObject;
	Transform*  m_transform;
	Rigidbody2D*  m_rigidbody;

	// Data
	Vector2 m_position;
	float	m_radius = 0.0f;
	float	m_normalfactor = 0.98f; // Closest to 1 is at 1.020073f due to floating point nonsense
	float   m_tangentfactor = 0.98f;

	// Projection Point
public:
	Vector2 calculateCollisionPoint(const LineCollider2D& c);
	CircleCollider2D(Transform* T);

	// Get Object Reference
	GameObject*	getGameObjectReference() const
	{
		return m_gameObject;
	}
	Transform*	getTransformReference() const
	{
		return m_transform;
	}
	
	// Collision Check
	bool checkCollision(const LineCollider2D& c);
	void collisionResponse(const LineCollider2D& c);

	// Update
	void Update(float delta) override;

	// Debug Draw
	void DrawOutline()
	{
		// A bit dumb, basically just an AABB box around a circle, but drawing circles in immediate mode aren't convenient
		App::DrawLineQuad(m_position, m_radius * 2, m_radius * 2);
	}
};