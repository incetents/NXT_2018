#pragma once

#include "../GameObject/Component.h"
#include "Collider.h"
#include "../App/SimpleLogger.h"
#include "../GameObject/RenderQueue.h"
#include "../Math/Vector2.h"
#include "../Math/Color.h"

class OBB2D : public Component, public Collider
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

	// Data (pos and size from transform)
	float rotation;

public:

	OBB2D(Transform* T);

	// Get Object Reference
	GameObject*	getGameObjectReference() const
	{
		return m_gameObject;
	}
	Transform*	getTransformReference() const
	{
		return m_transform;
	}

	// Get Position
	Vec2 getPosition() const;

	void Update(float delta) override;
	void Draw(Color3F color = Color3F::WHITE()) const override;

};