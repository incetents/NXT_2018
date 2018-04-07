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
		}

		//SimpleLogger.Print("TEST: " + std::to_string(m_velocity.x));

		// Increase Velocity
		m_velocity += m_gravity * m_gravityScale;
		// Cap Velocity
		if (m_velocity.Length() > m_terminalspeed)
			m_velocity.Resize(m_terminalspeed);

		// Increase Position
		m_transform->increasePosition(m_velocity + velocityQueue);

	}
}