#pragma once

#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix4x4.h"
#include "../Math/Transform.h"

class Camera
{
public:
	enum Type
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};
	// Transform of camera
	Transform   m_transform;
private:

	// Class can only be created from static functions
	Camera(Type t)
	{
		m_type = t;
	}

	// Variables
	Type		m_type;
	Matrix4x4	m_projection;
	Matrix4x4	m_projection_Inverse;
	Matrix4x4	m_view;
	Matrix4x4	m_view_Inverse;
	Matrix4x4	m_viewProjection;
	Matrix4x4	m_viewProjection_Inverse;

	// Create Projection from values
	void createOrthographic(float xmin, float xmax, float ymin, float ymax)
	{
		m_boundaries[0] = xmin;
		m_boundaries[1] = xmax;
		m_boundaries[2] = ymin;
		m_boundaries[3] = ymax;

		m_projection = Matrix4x4::GetOrthographic(
			m_boundaries[0], m_boundaries[1], // xmin, xmax
			m_boundaries[2], m_boundaries[3], // ymin, ymax
			m_znear, m_zfar
		);
		m_projection_Inverse = m_projection.Inverse();
	}
	void createPerspective(float fov, float aspect)
	{
		m_fov = fov;
		m_aspectRatio = aspect;

		m_projection = Matrix4x4::GetPerspective(
			m_fov, m_aspectRatio,
			m_znear, m_zfar
		);
		m_projection_Inverse = m_projection.Inverse();
	}

	// Orthographic Values
	float		m_boundaries[4]; // xmin, xmax, ymin, ymax
	// Perspective Values
	float		m_aspectRatio	= 1.0f;
	float		m_fov = 90.0f;
	// Values for both types
	void setNearFar(float znear, float zfar)
	{
		m_znear = znear;
		m_zfar = zfar;
	}
	float		m_znear			= 1.0f;
	float		m_zfar			= 100.0f;


public:

	// Use these functions to create cameras
	static Camera* createOrthographic(float xmin, float xmax, float ymin, float ymax, float znear, float zfar)
	{
		Camera* C = new Camera(Type::ORTHOGRAPHIC);
		C->setNearFar(znear, zfar);
		C->createOrthographic(xmin, xmax, ymin, ymax);
		return C;
	}
	static Camera* createPerspective(float fov, float* screenWidth, float* screenHeight, float znear, float zfar)
	{
		Camera* C = new Camera(Type::PERSPECTIVE);
		C->setNearFar(znear, zfar);
		C->createPerspective(fov, *screenWidth / *screenHeight);
		return C;
	}

	// Setters
	void setOrthographic(float xmin, float xmax, float ymin, float ymax, float znear, float zfar)
	{
		m_type = Type::ORTHOGRAPHIC;
		setNearFar(znear, zfar);
		createOrthographic(xmin, xmax, ymin, ymax);
	}
	void setPerspective(float fov, float* screenWidth, float* screenHeight, float znear, float zfar)
	{
		m_type = Type::PERSPECTIVE;
		setNearFar(znear, zfar);
		createPerspective(fov, *screenWidth / *screenHeight);
	}


	// Getters
	const Matrix4x4& getProjection() const
	{
		return m_projection;
	}
	const Matrix4x4& getView()
	{
		Vector3& P = m_transform.getPosition();
		return m_view = Matrix4x4::GetLookAt(P, P - Vector3::FORWARD, Vector3::UP);
	}
	const Matrix4x4 getViewProjection()
	{
		return getProjection() * getView();
	}

};