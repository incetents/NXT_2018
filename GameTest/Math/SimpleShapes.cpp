#include "stdafx.h"

#include "SimpleShapes.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Vertex.h"
#include "../Math/Color.h"
#include "../Math/MathCore.h"

/*
unsigned int indices_tri[] =
{
// Back
0, 1, 2,
0, 2, 3,
// Front
4, 6, 5,
4, 7, 6,
// LEFT
0, 5, 1,
0, 4, 5,
// RIGHT
3, 2, 6,
3, 6, 7,
// UP
1, 6, 2,
1, 5, 6,
// DOWN
0, 3, 7,
0, 7, 4
};
*/


SimpleShapes::SimpleShapes()
{
	Init();
}
void SimpleShapes::Init()
{
	// Init Check
	if (isInit)
		return;
	else
		isInit = true;

	// Create Vertex Arrays
	createCube();
	createBox();
	createBoxLeft();
	createBoxRight();
	createTriangle();
	createCircle();
}

void SimpleShapes::createBox()
{
	Vector3 box_vertices[] =
	{
		Vector3(-0.5f,-0.5f, 0.0f),
		Vector3(+0.5f,-0.5f, 0.0f),
		Vector3(+0.5f,+0.5f, 0.0f),
		Vector3(-0.5f,+0.5f, 0.0f),

		Vector3(-0.5f,-0.5f, 0.0f),
	};

	// Create Cube
	v_box = new VertexArray(5, VertexArray::Mode::LINE_STRIPS);
	v_box->setPositions(box_vertices, 5);
}
void SimpleShapes::createBoxLeft()
{
	Vector3 box_vertices[] =
	{
		Vector3(-0.0f,-0.5f, 0.0f),
		Vector3(+1.0f,-0.5f, 0.0f),
		Vector3(+1.0f,+0.5f, 0.0f),
		Vector3(-0.0f,+0.5f, 0.0f),

		Vector3(-0.0f,-0.5f, 0.0f),
	};

	// Create Cube
	v_box_left = new VertexArray(5, VertexArray::Mode::LINE_STRIPS);
	v_box_left->setPositions(box_vertices, 5);
}
void SimpleShapes::createBoxRight()
{
	Vector3 box_vertices[] =
	{
		Vector3(-1.0f,-0.5f, 0.0f),
		Vector3(+0.0f,-0.5f, 0.0f),
		Vector3(+0.0f,+0.5f, 0.0f),
		Vector3(-1.0f,+0.5f, 0.0f),

		Vector3(-1.0f,-0.5f, 0.0f),
	};

	// Create Cube
	v_box_right = new VertexArray(5, VertexArray::Mode::LINE_STRIPS);
	v_box_right->setPositions(box_vertices, 5);
}

void SimpleShapes::createCube()
{
	Vector3 cube_vertices[] =
	{
		// Back 4 vertices
		Vector3(-0.5f, -0.5f, -0.5f), // 0
		Vector3(-0.5f, +0.5f, -0.5f), // 1
		Vector3(+0.5f, +0.5f, -0.5f), // 2
		Vector3(+0.5f, -0.5f, -0.5f), // 3
	    // Front 4 vertices
	    Vector3(-0.5f, -0.5f, +0.5f), // 4
	    Vector3(-0.5f, +0.5f, +0.5f), // 5
	    Vector3(+0.5f, +0.5f, +0.5f), // 6
	    Vector3(+0.5f, -0.5f, +0.5f)  // 7
	};
	unsigned int cube_indices[] =
	{
		// back face
		0, 1,
		1, 2,
		2, 3,
		3, 0,
		// front face
		4, 5,
		5, 6,
		6, 7,
		7, 4,
		// Connecting lines
		0, 4,
		1, 5,
		2, 6,
		3, 7
	};
	Color3F cube_colors[] =
	{
		Color3F::WHITE(),
		Color3F::RED(),
		Color3F::RED(),
		Color3F::WHITE(),
		Color3F::WHITE(),
		Color3F::RED(),
		Color3F::RED(),
		Color3F::WHITE()
	};

	// Create Cube
	v_cube = new VertexArray(8, VertexArray::Mode::LINES);
	v_cube->setPositions(cube_vertices, 8);
	v_cube->setColors	(cube_colors,   8);
	v_cube->setIndices	(cube_indices, 24);
}

void SimpleShapes::createTriangle()
{
	Vector3 triangle_vertices[] =
	{
		Vector3(-SQRT_TWO_INV, -SQRT_TWO_INV, 0),
		Vector3(+SQRT_TWO_INV, -SQRT_TWO_INV, 0),
		Vector3(0, 1, 0)
	};
	unsigned int triangle_indices[] =
	{
		0, 1,
		1, 2,
		2, 0
	};

	// Create Triangle
	v_tri = new VertexArray(3, VertexArray::Mode::LINES);
	v_tri->setPositions(triangle_vertices, 3);
	v_tri->setIndices(triangle_indices, 6);
}

void SimpleShapes::createCircle()
{
	// 25 vertices for all points of a circle using all 360 degrees converted to radians
	Vector3 circle_vertices[] =
	{
		Vector3(sinf(Deg_To_Rad(000.f)), cosf(Deg_To_Rad(000.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(015.f)), cosf(Deg_To_Rad(015.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(030.f)), cosf(Deg_To_Rad(030.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(045.f)), cosf(Deg_To_Rad(045.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(060.f)), cosf(Deg_To_Rad(060.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(075.f)), cosf(Deg_To_Rad(075.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(090.f)), cosf(Deg_To_Rad(090.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(105.f)), cosf(Deg_To_Rad(105.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(120.f)), cosf(Deg_To_Rad(120.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(135.f)), cosf(Deg_To_Rad(135.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(150.f)), cosf(Deg_To_Rad(150.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(165.f)), cosf(Deg_To_Rad(165.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(180.f)), cosf(Deg_To_Rad(180.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(195.f)), cosf(Deg_To_Rad(195.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(210.f)), cosf(Deg_To_Rad(210.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(225.f)), cosf(Deg_To_Rad(225.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(240.f)), cosf(Deg_To_Rad(240.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(255.f)), cosf(Deg_To_Rad(255.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(270.f)), cosf(Deg_To_Rad(270.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(285.f)), cosf(Deg_To_Rad(285.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(300.f)), cosf(Deg_To_Rad(300.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(315.f)), cosf(Deg_To_Rad(315.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(330.f)), cosf(Deg_To_Rad(330.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(345.f)), cosf(Deg_To_Rad(345.f)), 0) * 0.5f,
		Vector3(sinf(Deg_To_Rad(360.f)), cosf(Deg_To_Rad(360.f)), 0) * 0.5f
	};
	// circle size is 1

	// Create Circle
	v_circle = new VertexArray(25, VertexArray::Mode::LINE_STRIPS);
	v_circle->setPositions(circle_vertices, 25);
}