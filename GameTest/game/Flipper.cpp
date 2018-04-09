#include "stdafx.h"

#include "Flipper.h"
#include "../Collision/OBB.h"
#include "../Collision/LineCollider.h"

Flipper::Flipper(
	std::string _name,
	Side bumperSide,
	float restAngle,
	float hitAngle,
	Vector2 position,
	Vector2 size) : GameObject(_name), m_restAngle(restAngle), m_hitAngle(hitAngle)
{

	// Data of self
	GetComponent<Transform>()->setPosition(position);
	GetComponent<Transform>()->setScale(Vector3(size, 0));

	float side_offset = 0.0f;
	if (bumperSide == Side::LEFT)
		side_offset += 0.5f;
	else
		side_offset -= 0.5f;

	m_angle = restAngle;

	Vector3 lines1[] =
	{
		Vector3(-0.5f + side_offset, -1.0f, 0),
		Vector3(+0.5f + side_offset, -1.0f, 0),
	};
	Vector3 lines2[] =
	{
		Vector3(+0.5f + side_offset, -1.0f, 0),
		Vector3(+0.5f + side_offset, +0.0f, 0),
	};
	Vector3 lines3[] =
	{
		Vector3(+0.5f + side_offset, +0.0f, 0),
		Vector3(-0.5f + side_offset, +0.0f, 0),
	};
	Vector3 lines4[] =
	{
		Vector3(-0.5f + side_offset, +0.0f, 0),
		Vector3(-0.5f + side_offset, -1.0f, 0),
	};
	Color3F colors[] =
	{
		Color3F::ORANGE(),
		Color3F::BLUE()
	};
	VertexArray* line1_v = new VertexArray(2, VertexArray::Mode::LINES);
	VertexArray* line2_v = new VertexArray(2, VertexArray::Mode::LINES);
	VertexArray* line3_v = new VertexArray(2, VertexArray::Mode::LINES);
	VertexArray* line4_v = new VertexArray(2, VertexArray::Mode::LINES);
	line1_v->setPositions(lines1, 2);
	line1_v->setColors(colors, 2);
	line2_v->setPositions(lines2, 2);
	line2_v->setColors(colors, 2);
	line3_v->setPositions(lines3, 2);
	line3_v->setColors(colors, 2);
	line4_v->setPositions(lines4, 2);
	line4_v->setColors(colors, 2);

	GameObject* line1 = new GameObject(line1_v, "FlipperPiece");
	GameObject* line2 = new GameObject(line2_v, "FlipperPiece");
	GameObject* line3 = new GameObject(line3_v, "FlipperPiece");
	GameObject* line4 = new GameObject(line4_v, "FlipperPiece");

	line1->renderer->m_lineWidth = 8.0f;
	line2->renderer->m_lineWidth = 8.0f;
	line3->renderer->m_lineWidth = 8.0f;
	line4->renderer->m_lineWidth = 8.0f;

	line1->AddComponent<>(new LineCollider2D(line1->transform));
	line2->AddComponent<>(new LineCollider2D(line2->transform));
	line3->AddComponent<>(new LineCollider2D(line3->transform));
	line4->AddComponent<>(new LineCollider2D(line4->transform));

	line1->GetComponent<LineCollider2D>()->setPoints(Vec2(lines1[0]), Vec2(lines1[1]));
	line2->GetComponent<LineCollider2D>()->setPoints(Vec2(lines2[0]), Vec2(lines2[1]));
	line3->GetComponent<LineCollider2D>()->setPoints(Vec2(lines3[0]), Vec2(lines3[1]));
	line4->GetComponent<LineCollider2D>()->setPoints(Vec2(lines4[0]), Vec2(lines4[1]));

	transform->addChild(line1->transform);
	transform->addChild(line2->transform);
	transform->addChild(line3->transform);
	transform->addChild(line4->transform);
	
}

void Flipper::Update(float delta)
{
	// Call gameobjects update
	GameObject::Update(delta);

	// Debug Angle
	//SimpleLogger.Print("Angle: " + toString(m_Angle));

	// Lerp Rotation
	if (m_actionState)
	{
		m_angle = MathCore::Lerp(m_angle, m_hitAngle, 0.33f);
		m_energy = MathCore::InverseLerp(m_angle, m_restAngle, m_hitAngle);
		// 0 to 1 -> 0.5 to 1
		//m_energy = m_energy * 0.5 + 0.5f;

		// No more energy at final state
		if (abs(m_angle - m_hitAngle) < 0.04f)
			m_energy = 0.0f;
	}
	else
	{
		m_angle = MathCore::Lerp(m_angle, m_restAngle, 0.33f);
		m_energy = 0.0f;
	}

	// Set Rotation
	transform->setRotationZ(m_angle);

	// Update Flipper Normal
	m_flipperNormal = (Vec2(0,1)).Rotate(Degrees(-m_angle));
	//bumperchild->GetComponent<OBB2D>()->UpdateRotation(m_Angle);

	// Set Flag
	m_actionState = false;
}