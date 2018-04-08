#include "stdafx.h"

#include "../GameObject/GameObject.h"
#include "../Math/Transform.h"
#include "../App/SimpleLogger.h"
#include "Rigidbody.h"

Rigidbody2D::Rigidbody2D(Transform* T)
{
	if (T == nullptr)
		return;

	m_transform = T;
	m_gameObject = T->getGameObjectReference();
}

void Rigidbody2D::Update(float delta)
{
	if (m_transform != nullptr)
	{
		Vec2 velocityQueue;
		// Add Velocity from queue
		if (m_velocityQueueCount > 0)
		{
			for (int i = 0; i < m_velocityQueueCount; i++)
			{
				velocityQueue += m_velocityQueue[i];
			}
			velocityQueue /= m_velocityQueueCount;
			m_velocityQueue.clear();
			m_velocityQueueCount = 0;
			// Override previous velocity
			m_velocity = Vec2();
		}

		// Increase Velocity
		m_velocity += (m_gravity * m_gravityScale) + velocityQueue;

		// Add Forces
		if (m_velocityForcesCount > 0)
		{
			for (int i = 0; i < m_velocityForcesCount; i++)
			{
				m_velocity += m_velocityForces[i];
			}
			m_velocityForces.clear();
			m_velocityForcesCount = 0;
		}

		// Cap Velocity
		if (m_velocity.Length() > m_terminalspeed)
			m_velocity.Resize(m_terminalspeed);

		// Increase Position
		m_transform->increasePosition(m_velocity);

	}
}