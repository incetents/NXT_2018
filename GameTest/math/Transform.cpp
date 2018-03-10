
#include "stdafx.h"

#include "Transform.h"

void Transform::updateEuler()
{
	m_rotation = Quaternion::GetEuler(Degrees(m_euler_rotation.x), Degrees(m_euler_rotation.y), Degrees(m_euler_rotation.z));
}

const Matrix4x4& Transform::getModel()
{
	// Apply Rotation and Translation at once	
	updateEuler();
	m_ModelMatrix = m_rotation.GetMatrix(m_position);
	// Multiply by Scale
	m_ModelMatrix[0x0] *= m_scale.x;
	m_ModelMatrix[0x5] *= m_scale.y;
	m_ModelMatrix[0xA] *= m_scale.z;
	return m_ModelMatrix;
}

Transform::Transform(const Vector3& position, const Vector3& euler_rotation, const Vector3& scale)
{
	m_position = position;
	m_scale = scale;
	m_euler_rotation = euler_rotation;
}