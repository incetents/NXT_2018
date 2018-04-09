#include "stdafx.h"

#include "../App/app.h"
#include "../GameObject/CameraManager.h"
#include "../Math/Transform.h"
#include "LineCollider.h"

LineCollider2D::LineCollider2D(Transform* T)
{
	if (T == nullptr)
		return;

	m_transform = T;
	m_gameObject = T->getGameObjectReference();
}

void LineCollider2D::setPoint1(Vector2 v)
{
	m_p1 = v;
}
void LineCollider2D::setPoint2(Vector2 v)
{
	m_p2 = v;
}
void LineCollider2D::setPoints(Vector2 v1, Vector2 v2)
{
	m_p1 = v1;
	m_p2 = v2;
}

Vector2 LineCollider2D::getDirection() const
{
	if (m_transform == nullptr)
		return (m_p2 - m_p1);

	Matrix4x4 model = m_transform->getModel();

	return (model * m_p2 - model * m_p1);
}
Vector2 LineCollider2D::getNormal() const
{
	if (m_transform == nullptr)
		return (m_p1 - m_p2).Perpendicular().Normalize();

	Matrix4x4 model = m_transform->getModel();

	return (model * m_p1 - model * m_p2).Perpendicular().Normalize();
}

// Get Points
Vector2 LineCollider2D::getPoint1() const
{
	if (m_transform == nullptr)
		return Vec2();

	return m_transform->getModel() * m_p1;
}
Vector2 LineCollider2D::getPoint2() const
{
	if (m_transform == nullptr)
		return Vec2();

	return m_transform->getModel() * m_p2;
}