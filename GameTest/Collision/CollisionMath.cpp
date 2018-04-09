#include "stdafx.h"

#include "CollisionMath.h"

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Transform.h"
#include "../Math/MathCore.h"

#include "../Utility/Utility.h"

#include "Circle.h"
#include "LineCollider.h"
#include "Rigidbody.h"
#include "OBB.h"

Vector2 calculateCollisionPoint(const CircleCollider2D& c, const LineCollider2D& l)
{
	Vec2 LineToCircle_Local = c.getPosition() - l.getPoint1();
	Vec2 Projection_Local = LineToCircle_Local.Project(l.getDirection());
	return Projection_Local + l.getPoint1();
}

// CHECKERS //

template<class A, class B>
bool CheckCollision(const A&, const B&)
{
	SimpleLogger.ErrorStatic("Collision Check Not Found");
	return false;
}

template<>
bool CheckCollision(const CircleCollider2D& c, const LineCollider2D& l)
{
	Vec2 position = c.getPosition();
	// Data
	Vec2 W1 = l.getPoint1();
	Vec2 W2 = l.getPoint2();
	Vec2 WD = l.getDirection();
	Vec2 WN = l.getNormal();

	// Check 1, see if ball is touching line <- (interpreted as infinitely long)
	bool Check1;
	Vec2 CollisionTarget = calculateCollisionPoint(c, l);
	float Projection_Distance = (position - CollisionTarget).Length();
	Check1 = Projection_Distance < c.getRadius();

	// Check for tunnelling instead
	if (!Check1)
	{
		Vec2 P1 = position;
		Vec2 P2 = position - c.getRigidbodyReference()->getVelocity();
		int CurrentSign = Utility::Sign(l.getNormal().Dot((P1 - W1).Normalize()));
		int NextSign = Utility::Sign(l.getNormal().Dot((P2 - W1).Normalize()));
		// If current and next sides of the line are the same, tunnelling has not occurred.
		if (CurrentSign == NextSign)
			return false;
		else
		{
			// Tunnel Safety
			c.getTransformReference()->setPosition(CollisionTarget);
		}
	}

	// Check 2, see if points from line edges to circle center are within the line length limit
	float CollToW1 = (CollisionTarget - W1).Length();
	float CollToW2 = (CollisionTarget - W2).Length();
	float line_length = l.getDirection().Length();
	bool Check2 = (CollToW1) <= line_length && (CollToW2) <= line_length;

	// Check 3, see if at least 1 line point is inside the sphere
	float BallToW1 = (position - W1).Length();
	float BallToW2 = (position - W2).Length();
	bool Check3 = (BallToW1) < c.getRadius() || (BallToW2) < c.getRadius();

	return Check2 || Check3;
}

template<>
bool CheckCollision(const LineCollider2D& l, const CircleCollider2D& c)
{
	return CheckCollision(c, l);
}

template<>
bool CheckCollision(const CircleCollider2D& c1, const CircleCollider2D& c2)
{
	return ((c1.getPosition() - c2.getPosition()).Length() < c1.getRadius() + c2.getRadius());
}

template<>
bool CheckCollision(const CircleCollider2D& c, const OBB2D& b)
{
	
	std::vector<Vec2> boxpoints = b.getPoints();
	Vec2 cpos = c.getPosition();
	float crad = c.getRadius();

	// Check if point is inside circle
	for (int i = 0; i < boxpoints.size(); i++)
	{
		if ((boxpoints[i] - cpos).Length() < crad)
			return true;
	}

	Vec2 axis1 = (boxpoints[1] - boxpoints[0]).Normalize();
	Vec2 axis2 = (boxpoints[2] - boxpoints[0]).Normalize();

	//
	//	Vec2 BoxToCircle = c.getPosition() - b.getPosition();
	//	float b_sin = sinf(Deg_To_Rad(b.getRotation()));
	//	float b_cos = sinf(Deg_To_Rad(b.getRotation()));
	//	
	//	float Offsetx = +BoxToCircle.x * b_cos + BoxToCircle.y * b_sin;
	//	float OffsetY = -BoxToCircle.x * b_sin + BoxToCircle.y * b_cos;
	//	
	//	Vec2 RotatedVec(Offsetx, OffsetY);
	//	
	//	Vec2 FixedVec;
	//	FixedVec.x = MacroClamp(RotatedVec.x, -b.getSize().x * 0.5f, +b.getSize().x * 0.5f);
	//	FixedVec.y = MacroClamp(RotatedVec.y, -b.getSize().y * 0.5f, +b.getSize().y * 0.5f);
	 
	return false;
}
template<>
bool CheckCollision(const OBB2D& b, const CircleCollider2D& c)
{
	return CheckCollision(c, b);
}

// RESOLVERS //

template<class A, class B>
void CollisionResponse(const A&, const B&)
{
	SimpleLogger.ErrorStatic("Collision Resolve Not Found");
}

template<>
void CollisionResponse(const CircleCollider2D& c, const LineCollider2D& l)
{
	Vec2 position = c.getPosition();

	// Cannot do collision without rigidbody (temp 'if' placement)
	if (c.getRigidbodyReference() != nullptr)
	{
		// Data
		Vec2 CollisionTarget = calculateCollisionPoint(c, l);
		Vec2 CircleToTarget = CollisionTarget - position;

		// Fix position
		// https://gamedev.stackexchange.com/questions/105296/calculation-correct-position-of-object-after-collision-2d?rq=1
		Vec2 LineDirection = l.getDirection().Normalize();
		Vec2 toCenter = (position - l.getPoint1());

		Vec2 perpComponent = toCenter - Vec2::Dot(toCenter, LineDirection) * LineDirection; //toCenter - Projection

		float penetrationDepth = c.getRadius() - perpComponent.Length();

		Vec2 mvmtToCorrectPosition = penetrationDepth * perpComponent.Normalize();
		c.getTransformReference()->increasePosition(mvmtToCorrectPosition);

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
		Vec2 Velocity = c.getRigidbodyReference()->getVelocity();
		Vector2 NormalV = Velocity.Project(CircleToTarget);
		Vector2 TangentV = Velocity - NormalV;
		Vector2 NewVelocity = (TangentV * c.getNormalFactor()) - (NormalV * c.getTangentFactor());

		// add to queue so it only updates after all collisions have occurred
		c.getRigidbodyReference()->addVelocityQueue(NewVelocity);
	}
}
template<>
void CollisionResponse(const LineCollider2D& l, const CircleCollider2D& c)
{
	CollisionResponse(c, l);
}

template<>
void CollisionResponse(const CircleCollider2D& c1, const CircleCollider2D& c2)
{
	Vec2 position = c1.getPosition();
	Vec2 other_position = c2.getPosition();

	// If it does not have a rigidbody (simple bounce)
	if (c2.getRigidbodyReference() == nullptr)
	{
		Vector2 Velocity = c1.getRigidbodyReference()->getVelocity();
		Vector2 Difference = (position - other_position);
		Vector2 NewVel = Vector2::Reflect(Velocity, Difference.Normalize());
		float ratio = (c1.getMass() / max(c1.getMass(), c2.getMass()));
		ratio += ratio * c1.getBounciness();

		// Fix Velocity
		c1.getRigidbodyReference()->addVelocityQueue(NewVel * ratio);

		// Fix position
		float offsetAmount = (c1.getRadius() + c2.getRadius()) - Difference.Length();
		Vector2 offset = Difference.Resize(offsetAmount);

		c1.getTransformReference()->increasePosition(offset);
	}
}
template<>
void CollisionResponse(const CircleCollider2D& c, const OBB2D& b)
{

}
template<>
void CollisionResponse(const OBB2D& b, const CircleCollider2D& c)
{
	CollisionResponse(c, b);
}
