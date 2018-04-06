#include "stdafx.h"

#include "../GameObject/GameObject.h"
#include "../Math/Transform.h"
#include "Rigidbody.h"

void Rigidbody::Update(float delta)
{
	if (m_transform != nullptr)
	{
		m_transform->increasePosition(m_velocity);
	}
}