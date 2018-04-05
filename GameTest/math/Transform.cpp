
#include "stdafx.h"

#include "Transform.h"
#include "../App/SimpleLogger.h"
#include "../App/app.h"
#include "../Math/Matrix4x4.h"

const Matrix4x4 Transform::getModel()
{
	// If dirty is true, update values
	if (isDirty)
	{
		// Update model matrix
		m_rotation = Quaternion::GetEuler(Degrees(m_euler_rotation.x), Degrees(m_euler_rotation.y), Degrees(m_euler_rotation.z));
		Matrix3x3 RotationScale = m_rotation.GetMatrix3x3() * Matrix3x3::GetScale(m_scale);
		m_ModelMatrix = Matrix4x4(RotationScale, m_position);

		// Update directions
		m_forward	= m_rotation * Vector3::FORWARD;
		m_right		= m_rotation * Vector3::RIGHT; // (Vector3::UP.Cross(m_forward)).Normalize();
		m_up		= m_forward.Cross(m_right);

		// Set Flag
		isDirty = false;
	}

	// Affected by parent
	if (m_parent != nullptr)
	{
		Matrix4x4 Parent = m_parent->getModel();
		Matrix4x4 Self = m_ModelMatrix;
		Matrix4x4 Final = Parent * Self;

		return m_parent->getModel() * m_ModelMatrix;
	}

	// Orphan
	return m_ModelMatrix;
}

Transform::Transform()
{
	m_position = Vector3(0, 0, 0);
	m_scale = Vector3(1, 1, 1);
	m_euler_rotation = Vector3(0, 0, 0);
}
Transform::Transform(const Vector3& position, const Vector3& euler_rotation, const Vector3& scale)
{
	m_position = position;
	m_scale = scale;
	m_euler_rotation = euler_rotation;
}

void Transform::drawDirections(const Matrix4x4& model)
{
	Vector3 P   = model * Vec3::ZERO;
	Vector3 P_F = model * (Vec3::FORWARD * 100.0f);
	Vector3 P_U = model * (Vec3::UP * 100.0f);
	Vector3 P_R = model * (Vec3::RIGHT * 100.0f);

	App::DrawLine(
		P, P_F,
		Color::RED, Color::RED
	);

	App::DrawLine(
		P, P_U,
		Color::BLUE, Color::BLUE
	);

	App::DrawLine(
		P, P_R,
		Color::GREEN, Color::GREEN
	);
}