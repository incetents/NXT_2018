#pragma once

#include "../Utility/Singleton.h"
#include "../GameObject/GameObject.h"

static class CollisionMath : public Singleton<class CollisionMath>
{
	friend class CircleCollider2D;
	friend class LineCollider2D;
	friend class OBB2D;
	friend class Vector2;

	friend Vector2 calculateCollisionPoint(const CircleCollider2D& c, const LineCollider2D& l);

	// CHECKERS //
	template<class A, class B>
	friend bool CheckCollision(const A& a, const B& b);

	// RESOLVERS
	template<class A, class B>
	friend void CollisionResponse(const A& a, const B& b);

public:
	// Do Collision Steps
	template<class A, class B>
	friend void UpdateCollision(A* a, B* b)
	{
		if (b == nullptr)
			return;

		// Respond to circle colliders
		if (CheckCollision(*a, *b))
		{
			// Respond if not trigger
			if (!b->m_isTrigger)
			{
				a->getGameObjectReference()->OnCollide(*b);
				b->getGameObjectReference()->OnCollide(*a);
				CollisionResponse(*a, *b);
			}
			else
			{
				a->getGameObjectReference()->OnTrigger(*b);
				b->getGameObjectReference()->OnTrigger(*a);
			}
		}
	}

} &CollisionMath = Singleton<class CollisionMath>::instanceRef;