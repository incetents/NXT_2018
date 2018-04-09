#pragma once

#include "../GameObject/Component.h"
#include "Collider.h"
#include "../App/SimpleLogger.h"
#include "../GameObject/RenderQueue.h"
#include "../Math/Color.h"
#include "../Math/Vector2.h"

class CircleCollider2D : public Component, public Collider
{
	friend class GameObject;
	friend class Transform;
	friend class Rigidbody2D;
	friend class LineCollider2D;
	friend class OBB2D;

private:
	// Data
	Vector2 m_offset;
	float	m_radius = 0.0f;
	float   m_mass = 0.0f;
	float   m_bounciness = 0.2f;
	float	m_normalfactor = 0.76f; // Closest to 1 is at 1.020073f due to floating point nonsense
	float   m_tangentfactor = 0.76f;

	// Projection Point
	Vector2 calculateCollisionPoint(const LineCollider2D& c);

public:
	CircleCollider2D(Transform* T);

	// Get Data
	Vec2 getPosition() const;
	float getRadius() const
	{
		return m_radius;
	}
	float getNormalFactor() const
	{
		return m_normalfactor;
	}
	float getTangentFactor() const
	{
		return m_tangentfactor;
	}
	float getMass() const
	{
		return m_mass;
	}
	float getBounciness() const
	{
		return m_bounciness;
	}
	
	// Collision Check
	void updateCollisions(GameObject* g);

	// Update
	void Init() override;
	void Update(float delta) override;
	void Draw(Color3F color = Color3F::WHITE()) const override;
};