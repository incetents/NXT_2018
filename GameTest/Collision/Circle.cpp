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
}

// Projection Point
Vector2 CircleCollider2D::calculateCollisionPoint(const LineCollider2D& c)
{
	Vec2 LineToCircle_Local = getPosition() - c.getPoint1();
	Vec2 Projection_Local = LineToCircle_Local.Project(c.getDirection());
	return Projection_Local + c.getPoint1();
}
bool CircleCollider2D::checkCollision(const CircleCollider2D& c)
{
	return ((getPosition() - c.getPosition()).Length() < m_radius + c.m_radius);
}
void CircleCollider2D::collisionResponse(const CircleCollider2D& c)
{
	Vec2 position = getPosition();
	Vec2 other_position = c.getPosition();
	// Activate Function
	m_gameObject->onCollide(c);

	// If it does not have a rigidbody (simple bounce)
	if (c.m_rigidbody == nullptr)
	{
		Vector2 Velocity = m_rigidbody->getVelocity();
		Vector2 Difference = (position - other_position);
		Vector2 NewVel = Vector2::Reflect(Velocity, Difference.Normalize());
		float ratio = (m_mass / max(c.m_mass, m_mass));
		ratio += ratio * c.m_bounciness;
		
		// Fix Velocity
		m_rigidbody->addVelocityQueue(NewVel * ratio);

		// Fix position
		float offsetAmount = (m_radius + c.m_radius) - Difference.Length();
		Vector2 offset = Difference.Resize(offsetAmount);

		m_transform->increasePosition(offset);
		position = m_transform->getPosition();
	}


	// If it has a rigidbody
	else
	{
		// Data
		Vector2 NewDirection = position - other_position;

		Vec2 Velocity = m_rigidbody->getVelocity();
		Vector2 NormalV1 = Velocity.Project(NewDirection);
		Vector2 NormalV2 = (c.m_rigidbody->getVelocity()).Project(NewDirection);
		Vector2 TangentV = Velocity - NormalV1;

		// Fix position
		float L = m_radius + c.m_radius - NewDirection.Length();
		float Vfix = (NormalV1 - NormalV2).Length();
		Vector2 Move = NormalV1.Resize(-L / Vfix);

		m_transform->increasePosition(Move);
		position = Move;

		// normal velocity components after the impact
		float m1 = m_mass;
		float m2 = c.m_mass;
		float u1 = NormalV1.ProjectLength(NewDirection);
		float u2 = NormalV2.ProjectLength(NewDirection);
		float v1 = ((m1 - m2)*u1 + 2 * m2*u2) / (m1 + m2);
		float v2 = ((m2 - m1)*u2 + 2 * m1*u1) / (m1 + m2);

		// normal velocity vectors after collision
		NormalV1 = NewDirection.Resize(v1);
		NormalV2 = NewDirection.Resize(v2);

		// Fix velocity
		m_rigidbody->addVelocityQueue(NormalV1 + TangentV);
		//ball1.velo2D = add(normalVelo1, tangentVelo1);
		//ball2.velo2D = add(normalVelo2, tangentVelo2);
	}
}

bool CircleCollider2D::checkCollision(const LineCollider2D& c)
{
	Vec2 position = getPosition();
	// Data
	Vec2 W1 = c.getPoint1();
	Vec2 W2 = c.getPoint2();
	Vec2 WD = c.getDirection();
	Vec2 WN = c.getNormal();

	// Check 1, see if ball is touching line <- (interpreted as infinitely long)
	bool Check1;
	Vec2 CollisionTarget = calculateCollisionPoint(c);
	float Projection_Distance = (position - CollisionTarget).Length();
	Check1 = Projection_Distance < m_radius;

	// Check for tunnelling instead
	if (!Check1)
	{
		Vec2 P1 = position;
		Vec2 P2 = position - m_rigidbody->getVelocity();
		int CurrentSign = Utility::Sign(c.getNormal().Dot((P1 - W1).Normalize()));
		int NextSign	= Utility::Sign(c.getNormal().Dot((P2 - W1).Normalize()));
		// If current and next sides of the line are the same, tunnelling has not occurred.
		if (CurrentSign == NextSign)
			return false;
		else
		{
			// Tunnel Safety
			m_transform->setPosition(CollisionTarget);
		}
	}

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
	float BallToW1 = (position - W1).Length();
	float BallToW2 = (position - W2).Length();
	bool Check3 = (BallToW1) < m_radius || (BallToW2) < m_radius;

	return Check2 || Check3;
}
void CircleCollider2D::collisionResponse(const LineCollider2D& c)
{
	Vec2 position = getPosition();
	// Activate Function
	m_gameObject->onCollide(c);

	// Cannot do collision without rigidbody (temp 'if' placement)
	if (m_rigidbody != nullptr)
	{
		// Data
		Vec2 CollisionTarget = calculateCollisionPoint(c);
		Vec2 CircleToTarget = CollisionTarget - position;
		
		// Fix position
		// https://gamedev.stackexchange.com/questions/105296/calculation-correct-position-of-object-after-collision-2d?rq=1
		Vec2 LineDirection = c.getDirection().Normalize();
		Vec2 toCenter = (position - c.getPoint1());

		Vec2 perpComponent = toCenter - Vec2::Dot(toCenter, LineDirection) * LineDirection; //toCenter - Projection

		float penetrationDepth = m_radius - perpComponent.Length();

		Vec2 mvmtToCorrectPosition = penetrationDepth * perpComponent.Normalize();
		m_transform->increasePosition(mvmtToCorrectPosition);
		position = m_transform->getPosition();

		// Fix position (also breaks, math is hard)
		/*
		float amountoffset = 0.0f;
		//int direction = Utility::Sign(CircleToTarget.Dot(Velocity));
		float d = (CircleToTarget.Normalize()).Dot(Velocity.Normalize());

		// - (center went past line)
		if (d < -0.95f)
			amountoffset = m_radius + CircleToTarget.Length();
		// + (center did not cross line)
		else
			amountoffset = m_radius - CircleToTarget.Length();

		Vec2 Move = Velocity.Resize(-(amountoffset));
		m_transform->increasePosition(Move);
		*/

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
		Vec2 Velocity = m_rigidbody->getVelocity();
		Vector2 NormalV =  Velocity.Project(CircleToTarget);
		Vector2 TangentV = Velocity - NormalV;
		Vector2 NewVelocity = (TangentV * m_tangentfactor) - (NormalV * m_normalfactor);

		// add to queue so it only updates after all collisions have occurred
		m_rigidbody->addVelocityQueue(NewVelocity); 

		// Original
		//m_rigidbody->setVelocity(NewVelocity);
	}
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