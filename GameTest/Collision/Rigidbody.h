#pragma once

#include "../GameObject/Component.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"


class Rigidbody : public Component
{
	friend class GameObject;
	friend class Transform;
private:
	// Object References
	GameObject* m_gameObject = nullptr;
	Transform* m_transform = nullptr;

	// Data
	Vector3 m_gravity = Vector3(0, -1, 0);
	float	m_gravityScale = 0.0f;
	const float m_terminalspeed = 20.0f;

	Vector3 m_velocity = Vector3(0, 0, 0);

public:
	// Requires GameObject as reference
	Rigidbody(Transform* reference);

	// GameObject Reference
	Transform*  getTransformReference() const
	{
		return m_transform;
	}
	GameObject*	getGameObjectReference() const
	{
		return m_gameObject;
	}

	// Set Data
	inline void setVelocity(Vector3 v)
	{
		m_velocity = v;
	}
	inline void setVelocity(Vector2 v)
	{
		m_velocity = Vector3(v, 0);
	}
	inline void setGravityDirection(Vector3 v)
	{
		m_gravity = v.Normalize();
	}
	inline void setGravityAmount(float f)
	{
		m_gravityScale = f;
	}
	
	// Increasers
	inline void increaseVelocity(Vector3 v)
	{
		m_velocity += v;
	}
	inline void increaseVelocity(Vector2 v)
	{

	}

	// Get Data
	inline Vector3 getVelocity() const
	{
		return m_velocity;
	}

	void Update(float delta) override;
};