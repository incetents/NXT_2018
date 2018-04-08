#include "stdafx.h"

#include "../App/app.h"
#include "../Math/Matrix4x4.h"
#include "../Math/Rotation.h"
#include "../Math/Transform.h"
#include "Circle.h"
#include "LineCollider.h"
#include "Rigidbody.h"
#include "OBB.h"
#include "CollisionMath.h"

#include "../GameObject/GameObject.h"
#include "../App/SimpleLogger.h"
#include "../Utility/Utility.h"

CircleCollider2D::CircleCollider2D(Transform* T)
{
	if (T == nullptr)
		return;

	m_transform = T;
	m_gameObject = T->getGameObjectReference();
	m_rigidbody = m_gameObject->GetComponent<Rigidbody2D>();
}

// Projection Point
Vector2 CircleCollider2D::calculateCollisionPoint(const LineCollider2D& c)
{
	Vec2 LineToCircle_Local = getPosition() - c.getPoint1();
	Vec2 Projection_Local = LineToCircle_Local.Project(c.getDirection());
	return Projection_Local + c.getPoint1();
}

void CircleCollider2D::updateCollisions(GameObject* g)
{
	// Error Check
	if (g == nullptr)
		return;

	// Respond to possible colliders
	auto L = g->GetComponent<LineCollider2D>();
	auto C = g->GetComponent<CircleCollider2D>();
	auto B = g->GetComponent<OBB2D>();

	UpdateCollision<>(this, L);
	UpdateCollision<>(this, C);
	UpdateCollision<>(this, B);
}

Vec2 CircleCollider2D::getPosition() const
{
	if (m_transform == nullptr)
	{
		SimpleLogger.ErrorStatic("Getting Position from null Transform");
		return Vec2();
	}
	return Vec2(m_transform->getPosition());
}

void CircleCollider2D::Init()
{
	// a bit of a simplifcation
	m_radius = m_transform->getScale().x * 0.5f;
	m_mass = m_radius;
}

void CircleCollider2D::Update(float delta)
{
	// a bit of a simplifcation
	m_radius = m_transform->getScale().x * 0.5f;
	m_mass = m_radius;
}

void CircleCollider2D::Draw(Color3F color) const
{
	// I cheaped out and just drew a box around the circle
	if (m_transform != nullptr)
	{
		Matrix4x4 model = m_transform->getModel();

		Vec3 Pos1 = model * Vec3(-0.5f, -0.5f, 0);
		Vec3 Pos2 = model * Vec3(+0.5f, -0.5f, 0);
		Vec3 Pos3 = model * Vec3(+0.5f, +0.5f, 0);
		Vec3 Pos4 = model * Vec3(-0.5f, +0.5f, 0);

		App::DrawLine(Pos1, Pos2, color, color);
		App::DrawLine(Pos2, Pos3, color, color);
		App::DrawLine(Pos3, Pos4, color, color);
		App::DrawLine(Pos4, Pos1, color, color);
	}
}

