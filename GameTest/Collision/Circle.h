#pragma once

#include "../GameObject/Component.h"

class CircleCollider2D : public Component
{
	friend class Vector2;
	friend class GameObject;
	friend class Transform;
	friend class Rigidbody;
	friend class LineCollider2D;

private:
	// Object References
	GameObject* m_gameObject;
	Transform*  m_transform;
	Rigidbody*  m_rigidbody;

	// Data
	Vector2 m_position;
	float	m_radius = 0.0f;
	float	m_normalfactor = 1.0f;
	float   m_tangentfactor = 1.0f;
public:
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
	void Draw()
	{
		//App::DrawLine(Vector2(100, 100), Vector2(300, 300));
		App::DrawLineQuad(m_position, m_radius * 2, m_radius * 2);
	}
};