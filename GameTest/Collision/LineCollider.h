#pragma once

#include "../GameObject/Component.h"
#include "../Math/Vector2.h"

class LineCollider2D : public Component
{
	friend class Vector2;
	friend class GameObject;
	friend class Transform;
private:
	// Object References
	GameObject* m_gameObject = nullptr;
	Transform* m_transform = nullptr;
	
	// Data
	Vector2 m_p1;
	Vector2 m_p2;
public:
	LineCollider2D(Transform* T);

	// Get Object Reference
	GameObject*	getGameObjectReference() const
	{
		return m_gameObject;
	}
	Transform*	getTransformReference() const
	{
		return m_transform;
	}

	// Set Points
	void setPoint1(Vector2 v);
	void setPoint2(Vector2 v);
	void setPoints(Vector2 v1, Vector2 v2);

	// Get Points
	Vector2 getPoint1() const
	{
		return m_p1;
	}
	Vector2 getPoint2() const
	{
		return m_p2;
	}

	// Get Data
	Vector2 getDirection() const;
	Vector2 getNormal() const;




};