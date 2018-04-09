#include "stdafx.h"

#include "Wall.h"

#include "../App/SimpleLogger.h"
#include "../GameObject/Renderer.h"
#include "../Math/SimpleShapes.h"
#include "../Math/Color.h"
#include "../Collision/Rigidbody.h"
#include "../Collision/Circle.h"
#include "../Collision/LineCollider.h"

Wall::Wall(
	std::string _name,
	Vector2 position1,
	Vector2 position2,
	Color3F color1,
	Color3F color2
	) : GameObject(_name)
{
	// Set Data
	point1 = position1;
	point2 = position2;

	// Create Shape
	Vector3 vertices[] =
	{
		Vector3(position1),
		Vector3(position2)
	};
	Color3F colors[] =
	{
		color1,
		color2
	};
	VertexArray* VA_Wall = new VertexArray(2, VertexArray::LINES);
	VA_Wall->setPositions(vertices, 2);
	VA_Wall->setColors(colors, 2);

	GetComponent<Renderer>()->setVertexArray(VA_Wall);

	// Components
	AddComponent(new LineCollider2D(transform));
	GetComponent<LineCollider2D>()->setPoints(point1, point2);
}

void Wall::UpdatePoint1(Vec2 p1)
{
	point1 = p1;

	GetComponent<LineCollider2D>()->setPoints(point1, point2);
}
void Wall::UpdatePoint2(Vec2 p2)
{
	point2 = p2;

	GetComponent<LineCollider2D>()->setPoints(point1, point2);
}
void Wall::UpdatePoints(Vec2 p1, Vec2 p2)
{
	point1 = p1;
	point2 = p2;

	GetComponent<LineCollider2D>()->setPoints(point1, point2);
}
void Wall::setThickness(float amount)
{
	renderer->m_lineWidth = amount;
}