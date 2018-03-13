#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Rotation.h"

class Transform
{
private:
	Matrix4x4	m_ModelMatrix;
	Vector3		m_position;
	Vector3		m_euler_rotation;
	Vector3		m_scale;
	Quaternion	m_rotation;

	void updateEuler();
	
public:
	Transform();
	Transform(const Vector3& position, const Vector3& euler_rotation, const Vector3& scale);

	const Matrix4x4& getModel();

	// Setters
	inline void setPosition(const Vector3& position)
	{
		m_position = position;
	}
	inline void setRotation(const Vector3& euler_rotation)
	{
		m_euler_rotation = euler_rotation;
	}
	inline void setScale(const Vector3 scale)
	{
		m_scale = scale;
	}

	// Increasers
	inline void increasePosition(const Vector3& translate)
	{
		m_position += translate;
	}
	inline void increaseRotation(const Vector3& euler_increase)
	{
		m_euler_rotation += euler_increase;
	}
	inline void increaseScale(const Vector3& scaler)
	{
		m_scale += scaler;
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
};