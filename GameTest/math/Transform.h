#pragma once

#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Rotation.h"

class Transform
{
private:
	// Model for transformations
	Matrix4x4	m_ModelMatrix;

	// Raw Values
	Vector3		m_position;
	Vector3		m_euler_rotation;
	Vector3		m_scale;
	Quaternion	m_rotation;

	// Direction Space
	Vector3		m_forward = Vector3::FORWARD;
	Vector3     m_up = Vector3::UP;
	Vector3     m_right = Vector3::RIGHT;

	Transform*  m_parent = nullptr;

	bool isDirty = true;
	
public:
	Transform();
	Transform(const Vector3& position, const Vector3& euler_rotation, const Vector3& scale);

	const Matrix4x4 getModel();

	// Parent / Child
	void setParent(Transform* parent)
	{
		// canoot parent self
		if (parent == this)
			return;

		m_parent = parent;
	}

	// Setters
	inline void setPosition(const Vector3& position)
	{
		m_position = position;
		isDirty = true;
	}
	inline void setRotation(const Vector3& euler_rotation)
	{
		m_euler_rotation = euler_rotation;
		isDirty = true;
	}
	inline void setScale(const Vector3 scale)
	{
		m_scale = scale;
		isDirty = true;
	}
	inline void setScale(float scaleAll)
	{
		m_scale = Vector3(scaleAll);
		isDirty = true;
	}

	// Increasers
	inline void increasePosition(const Vector3& translate)
	{
		m_position += translate;
		isDirty = true;
	}
	inline void increaseRotation(const Vector3& euler_increase)
	{
		m_euler_rotation += euler_increase;
		isDirty = true;
	}
	inline void increaseScale(const Vector3& scaler)
	{
		m_scale += scaler;
		isDirty = true;
	}

	// Getters
	inline Vector3		getPosition() const
	{
		return m_position;
	}
	inline Vector3		getRotationEuler() const
	{
		return m_euler_rotation;
	}
	inline Quaternion	getRotation() const
	{
		return m_rotation;
	}
	inline Vector3		getScale() const
	{
		return m_scale;
	}
	inline Vector3		getForward() const
	{
		return m_forward;
	}
	inline Vector3		getUp() const
	{
		return m_up;
	}
	inline Vector3		getRight() const
	{
		return m_right;
	}

	// Special
	void drawDirections();
};