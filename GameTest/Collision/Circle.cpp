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
#include "../Utility/Utility.h"

CircleCollider2D::CircleCollider2D(Transform* T)
{
	if (T == nullptr)
		return;

	m_transform = T;
	m_gameObject = T->getGameObjectReference();
	m_rigidbody = m_gameObject->GetComponent<Rigidbody2D>();

	if (m_rigidbody == nullptr)
		SimpleLogger.ErrorStatic("Rigidbody missing");
}

// Projection Point
Vector2 CircleCollider2D::calculateCollisionPoint(const LineCollider2D& c)
{
	Vec2 LineToCircle_Local = m_position - c.getPoint1();
	Vec2 Projection_Local = LineToCircle_Local.Project(c.getDirection());
	return Projection_Local + c.getPoint1();
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
	Vec2 CollisionTarget = calculateCollisionPoint(c);
	float Projection_Distance = (m_position - CollisionTarget).Length();
	Check1 = Projection_Distance < m_radius;

	if (!Check1)
		return false;

	// Draw Collision Point
#if _DEBUG
	//	App::DrawLine(
	//		CollisionTarget + Vec2(-1,+1) * 24.0f,
	//		CollisionTarget + Vec2(+1,-1) * 24.0f);
	//	
	//	App::DrawLine(
	//		CollisionTarget + Vec2(+1, +1) * 24.0f,
	//		CollisionTarget + Vec2(-1, -1) * 24.0f);
#endif

	// Check 2, see if points from line edges to circle center are within the line length limit
	float CollToW1 = (CollisionTarget - W1).Length();
	float CollToW2 = (CollisionTarget - W2).Length();
	float line_length = c.getDirection().Length();
	bool Check2 = (CollToW1) <= line_length && (CollToW2) <= line_length;

	// Check 3, see if at least 1 line point is inside the sphere
	float BallToW1 = (m_position - W1).Length();
	float BallToW2 = (m_position - W2).Length();
	bool Check3 = (BallToW1) < m_radius || (BallToW2) < m_radius;

	return Check2 || Check3;
}
void CircleCollider2D::collisionResponse(const LineCollider2D& c)
{
	//SimpleLogger.ErrorStatic("Collision");

	// Cannot do collision without rigidbody (temp 'if' placement)
	if (m_rigidbody != nullptr)
	{
		// Data
		Vec2 CollisionTarget = calculateCollisionPoint(c);
		Vec2 CircleToTarget = CollisionTarget - m_position;
		Vec2 Velocity = m_rigidbody->getVelocity();
		
		// Fix position
		float amountoffset1 = m_radius + CircleToTarget.Length();
		float amountoffset2 = m_radius - CircleToTarget.Length();

		int direction = Utility::Sign(CircleToTarget.Dot(Velocity));

		if(direction < 0) // -
			m_transform->increasePosition(Vec2::Resize(Velocity, -amountoffset1));
		else // +
			m_transform->increasePosition(Vec2::Resize(Velocity, -amountoffset2));

		// Fix Position (doesn't work all the time for some reason)
		/*
		float Offset = CircleToTarget.Dot(c.getNormal());
		
		float Angle_Direction_Wall = Vec2::GetAngleRadians(c.getDirection(), Velocity).Get();
		
		float DeltaS;
		if (abs(sinf(Angle_Direction_Wall)) == 0.0f)
			DeltaS = 0.0f;
		else
			DeltaS = m_radius + Offset / sinf(Angle_Direction_Wall);
		
		Vector2 Displacement = Vector2::Resize(Velocity, -(DeltaS));
		
		m_transform->increasePosition(Displacement);
		m_position = m_transform->getPosition();
		*/

		// Fix Velocity
		Vector2 NormalV =  Velocity.Project(CircleToTarget);
		Vector2 TangentV = Velocity - NormalV;
		Vector2 NewVelocity = (TangentV * m_tangentfactor) - (NormalV * m_normalfactor);

		m_rigidbody->addVelocityQueue(NewVelocity);
		//m_rigidbody->setVelocity(NewVelocity);
	}
}

void CircleCollider2D::Update(float delta)
{
	m_position = m_transform->getPosition();
	m_radius = m_transform->getScale().x * 0.5f;
}