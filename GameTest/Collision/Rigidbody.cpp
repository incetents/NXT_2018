#include "stdafx.h"

#include "../GameObject/GameObject.h"
#include "../Math/Transform.h"
#include "../App/SimpleLogger.h"
#include "Rigidbody.h"

Rigidbody::Rigidbody(Transform* T)
{
	if (T == nullptr)
		return;

	m_transform = T;
	m_gameObject = T->getGameObjectReference();
}

void Rigidbody::Update(float delta)
{
	if (m_transform != nullptr)
	{
		//SimpleLogger.Print("TEST: " + std::to_string(m_velocity.x));

		// Increase Velocity
		m_velocity += m_gravity * m_gravityScale;
		// Cap Velocity
		if (m_velocity.Length() > m_terminalspeed)
			m_velocity.Resize(m_terminalspeed);

		// Increase Position
		m_transform->increasePosition(m_velocity);

	}
}