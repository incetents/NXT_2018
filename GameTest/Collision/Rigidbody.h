#pragma once

#include "../GameObject/Component.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"

class GameObject;
class Transform;

class Rigidbody : public Component
{
private:
	// Object References
	GameObject* m_gameObject = nullptr;
	Transform* m_transform = nullptr;

	// Data
	Vector3 m_gravity = Vector3(0, -1, 0);;
	float	m_gravityScale = 0.0f;

	Vector3 m_velocity = Vector3(0, 0, 0);

public:
	// GameObject Reference
	void				setGameObjectReference(GameObject* G)
	{
		if (m_gameObject == nullptr)
			return;

		m_gameObject = G;

		if (m_gameObject->GetComponent<Transform>() != nullptr)
			m_transform = m_gameObject->GetComponent<Transform>();
	}
	const GameObject*	getGameObjectReference() const
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
	
	// Get Data
	inline Vector3 getVelocity() const
	{
		return m_velocity;
	}

	void Update(float delta) override;
};