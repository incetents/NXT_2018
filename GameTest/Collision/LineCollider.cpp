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
	return (m_p2 - m_p1);
}
Vector2 LineCollider2D::getNormal() const
{
	return (m_p2 - m_p1).Perpendicular().Normalize();
}