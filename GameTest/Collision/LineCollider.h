#pragma once

#include "../Math/Vector2.h"
#include "../Math/Matrix4x4.h"
#include "../GameObject/CameraManager.h"
#include "../GameObject/Component.h"
#include "../App/app.h"

class LineCollider2D : public Component
{
private:
	
public:
	LineCollider2D(){}

	Vector2 m_p1;
	Vector2 m_p2;

	void Draw()
	{
		App::DrawLine(
			m_p1,
			m_p2,
			Color::RED, Color::GREEN
		);
	}
	void Draw(const Matrix4x4& model)
	{
		App::DrawLine(
			model* m_p1,
			model* m_p2,
			Color::RED, Color::GREEN
		);
	}

};