#include "stdafx.h"

#include "../App/app.h"
#include "../Math/Matrix4x4.h"
#include "../Math/Vector2.h"
#include "../Math/Rotation.h"
#include "../Math/Transform.h"
#include "Circle.h"
#include "LineCollider.h"
#include "Rigidbody.h"
#include "../GameObject/GameObject.h"
#include "../App/SimpleLogger.h"

CircleCollider2D::CircleCollider2D(Transform* T)
{
	if (T == nullptr)
		return;

	m_transform = T;
	m_gameObject = T->getGameObjectReference();
	m_rigidbody = m_gameObject->GetComponent<Rigidbody>();

	if (m_rigidbody == nullptr)
		SimpleLogger.ErrorStatic("Rigidbody missing");
}

bool CircleCollider2D::checkCollision(const LineCollider2D& c)
{
	// Data
	Vec2 W1 = c.getPoint1();
	Vec2 W2 = c.getPoint2();
	Vec2 WD = c.getDirection();
	Vec2 WN = c.getNormal();

	// Check 1, see if ball is touching line <- (interpreted as infinitely long)
	bool Check1;
	Vec2 LineToCircle_Local = m_position - W1;
	Vec2 Projection_Local = LineToCircle_Local.Project(WD);
	Vec2 Projection_Global = Projection_Local + W1;
	float Projection_Distance = (m_position - Projection_Global).Length();
	Check1 = Projection_Distance < m_radius;

	// Check 2

	return Check1;
}
void CircleCollider2D::collisionResponse(const LineCollider2D& c)
{
	// Cannot do collision without rigidbody (temp 'if' placement)
	if (m_rigidbody != nullptr)
	{
		// Check Projection Hit Point
		Vec2 Projection_Global = ((m_position - c.getPoint1()).Project(c.getDirection())) + c.getPoint1();
		Vec2 BallToProjection = m_position - Projection_Global;
		
		// Fix Position
		float Angle_Direction_Wall = Vec2::GetAngleDegrees(c.getDirection(), Vector2(m_rigidbody->getVelocity())).Get();
		
		float DeltaS;
		if (abs(sinf(Angle_Direction_Wall)) < 0.0001f)
			DeltaS = 0.0f;
		else
			DeltaS = m_radius + BallToProjection.Dot(c.getNormal()) / sinf(Angle_Direction_Wall);
		
		Vector3 Displacement = Vector3::Resize(m_rigidbody->getVelocity(), -DeltaS);
		
		m_transform->increasePosition(Displacement);

		SimpleLogger.ErrorStatic("Collision");
		m_rigidbody->setVelocity(Vec2(0, 0));
		m_rigidbody->setGravityAmount(0.0f);
		// Fix Velocity
		//m_rigidbody->setVelocity(-m_rigidbody->getVelocity());
	}
}

void CircleCollider2D::Update(float delta)
{
	m_position = m_transform->getPosition();
	m_radius = m_transform->getScale().x * 1.0f;
}