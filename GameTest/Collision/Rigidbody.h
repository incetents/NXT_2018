#pragma once

#include "../GameObject/Component.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"


class Rigidbody2D : public Component
{
	friend class GameObject;
	friend class Transform;
protected:
	// Object References
	GameObject* m_gameObject = nullptr;
	Transform* m_transform = nullptr;

	// Data
	Vector2 m_gravity = Vector2(0, -1);
	float	m_gravityScale = 0.0f;
	const float m_terminalspeed = 20.0f;
	bool m_enabled = true;

	Vector2 m_velocity = Vector2(0, 0);

	// Velocity Queue
	float m_velocityQueueCount = 0;
	std::vector<Vector2> m_velocityQueue;

	// Forces
	size_t m_velocityForcesCount = 0;
	std::vector<Vector2> m_velocityForces;

public:
	// Requires GameObject as reference
	Rigidbody2D(Transform* reference);

	// GameObject Reference
	Transform*  getTransformReference() const
	{
		return m_transform;
	}
	GameObject*	getGameObjectReference() const
	{
		return m_gameObject;
	}

	// Add Reaction Velocity - Adds To Queue (only changes velocity in update)
	inline void addVelocityQueue(Vector2 v)
	{
		m_velocityQueue.push_back(v);
		m_velocityQueueCount++;
	}

	// Add Force to velocity
	inline void addForce(Vector2 v)
	{
		m_velocityForces.push_back(v);
		m_velocityForcesCount++;
	}

	// Update Overrider
	inline void setActive(bool state)
	{
		m_enabled = state;
	}
	inline bool checkActive()
	{
		return m_enabled;
	}

	// Set Data
	inline void setVelocity()
	{
		m_velocity = Vec2(0, 0);
	}
	inline void setVelocity(Vector2 v)
	{
		m_velocity = v;
	}
	inline void setGravityDirection(Vector2 v)
	{
		m_gravity = v.Normalize();
	}
	inline void setGravityAmount(float f)
	{
		m_gravityScale = f;
	}
	
	// Increasers
	inline void increaseVelocity(Vector2 v)
	{
		m_velocity += v;
	}

	// Get Data
	inline Vector2 getVelocity() const
	{
		return m_velocity;
	}

	void Update(float delta) override;
};