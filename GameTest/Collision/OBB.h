#pragma once

#include "../GameObject/Component.h"
#include "Collider.h"
#include "../App/SimpleLogger.h"
#include "../GameObject/RenderQueue.h"
#include "../Math/Vector2.h"
#include "../Math/Color.h"
#include <vector>

class OBB2D : public Component, public Collider
{
	friend class Vector2;
	friend class GameObject;
	friend class Transform;
	friend class Rigidbody2D;
	friend class LineCollider2D;

private:


	// Data (pos and size from transform)
	float m_rotation = 0.0f;

public:

	OBB2D(Transform* T);


	// Get Data
	Vec2 getPosition() const;
	Vec2 getSize() const;
	float getRotation() const
	{
		return m_rotation;
	}
	std::vector<Vec2> getPoints() const;

	void UpdateRotation(float z)
	{
		m_rotation = z;
	}
	void Update(float delta) override;
	void Draw(Color3F color = Color3F::WHITE()) const override;

};