#pragma once

#include "../GameObject/GameObject.h"
#include "../App/SimpleLogger.h"
#include "../Math/SimpleShapes.h"
#include "../Math/MathCore.h"

class Bumper : public GameObject
{
public:
	GameObject* bumperchild;
	enum class Side
	{
		LEFT,
		RIGHT
	};
private:
	Side m_side;
	float m_restAngle = 0.0f;
	float m_hitAngle = 45.0f;
	float m_Angle = 0.0f;
	bool m_actionState = false;
public:
	
	Bumper(
		std::string _name = "",
		Side bumperSide = Side::LEFT,
		float restAngle = 0.0f,
		float hitAngle = 45.0f,
		Vector2 position = Vector2(0, 0),
		Vector2 size = Vector2(1, 1)
	);

	void Action()
	{
		m_actionState = true;
	}

	void Update(float delta) override
	{
		// Call gameobjects update
		GameObject::Update(delta);

		// Debug Angle
		//SimpleLogger.Print("Angle: " + toString(m_Angle));

		// Lerp Rotation
		if (m_actionState)
			m_Angle = MathCore::Lerp(m_Angle, m_hitAngle, 0.63f);
		else
			m_Angle = MathCore::Lerp(m_Angle, m_restAngle, 0.33f);

		// Set Rotation
		transform->setRotationZ(m_Angle);

		// Set Flag
		m_actionState = false;
	}

};