
#pragma once

class Collider
{
protected:
	friend class GameObject;
	friend class Transform;
	friend class Rigidbody2D;

	// Object References
	GameObject* m_gameObject = nullptr;
	Transform* m_transform = nullptr;
	Rigidbody2D*  m_rigidbody;

public:
	// Get Object Reference
	GameObject*	getGameObjectReference() const
	{
		return m_gameObject;
	}
	Transform*	getTransformReference() const
	{
		return m_transform;
	}
	Rigidbody2D*	getRigidbodyReference() const
	{
		return m_rigidbody;
	}

	bool m_isTrigger = false;
};