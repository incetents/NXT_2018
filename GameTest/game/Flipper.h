#pragma once

#include "../GameObject/GameObject.h"
#include "../App/SimpleLogger.h"
#include "../Math/SimpleShapes.h"
#include "../Math/MathCore.h"

class Flipper : public GameObject
{
public:
	//GameObject* bumperchild;
	std::vector<GameObject*> flipperlines;
	enum class Side
	{
		LEFT,
		RIGHT
	};
private:
	Side  m_side;
	float m_restAngle = 0.0f;
	float m_hitAngle = 45.0f;
	float m_angle = 0.0f;
	bool  m_actionState = false;
	Vec2  m_flipperNormal = Vec2(0, 1);
	float m_energy = 0.0f;
	float m_strength = 30.0f;
public:
	
	Flipper(
		std::string _name = "",
		Side bumperSide = Side::LEFT,
		float restAngle = 0.0f,
		float hitAngle = 45.0f,
		Vector2 position = Vector2(0, 0),
		Vector2 size = Vector2(1, 1)
	);

	float getEnergy()
	{
		return m_energy;
	}
	Vec2 getFlipperNormal()
	{
		return m_flipperNormal;
	}
	float getStrength()
	{
		return m_strength;
	}

	void Action()
	{
		m_actionState = true;
	}

	void Update(float delta) override;

};