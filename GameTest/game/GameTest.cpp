//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <iostream>
//------------------------------------------------------------------------
#include "../app/app.h"
#include "../App/AppSettings.h"
#include "../app/Logger.h"

#include "../math/Transform.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/CameraManager.h"
#include "../Particle/Emitter.h"

int ScreenWidth = APP_VIRTUAL_WIDTH;
int ScreenHeight = APP_VIRTUAL_HEIGHT;

Logger logger(5, 5, 3);

LogData<float>* log_angle;
LogMessage* log_x1;
LogMessage* log_y1;
LogMessage* log_x2;
LogMessage* log_y2;
LogMessage* log_x3;
LogMessage* log_y3;
//LogMessage* log_info1;

Vector3 vertices[] =
{
	// Back 4 vertices
	Vector3(-25, -25, -25), // 0
	Vector3(-25, +25, -25), // 1
	Vector3(+25, +25, -25), // 2
	Vector3(+25, -25, -25), // 3
	// Front 4 vertices
	Vector3(-25, -25, +25), // 4
	Vector3(-25, +25, +25), // 5
	Vector3(+25, +25, +25), // 6
	Vector3(+25, -25, +25)  // 7
};

unsigned int indices[] =
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

Vector3 line_tri_vert[] =
{
	Vector3(-25, -25, 0),
	Vector3(+25, -25, 0),

	Vector3(+25, -25, 0),
	Vector3(0, 25, 0),

	Vector3(0, 25, 0),
	Vector3(-25, -25, 0)
};

VertexArray* VA_Box_Lines;
//VertexArray VA_Box_Tris(vertices, indices_tri, colors, 8, 36, VertexArray::Mode::TRIANGLE);

VertexArray* VA_tri_line;

GameObject* G_Box1;
GameObject* G_Box2;
GameObject* G_Tri;

Emitter* E_1;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	Color3F colors[] =
	{
		Color::WHITE,
		Color::RED,
		Color::RED,
		Color::WHITE,
		Color::WHITE,
		Color::RED,
		Color::RED,
		Color::WHITE
	};

	App::CullMode(CullType::COUNTER_CLOCKWISE);

	//log_angle = logger.addDataMessage("Angle: ", 0.0f, Color3F::getColor(ColorIndex::PURPLE));
	//log_tri_x = logger.addDataMessage("X: ", 0.0f);
	//log_tri_y = logger.addDataMessage("Y: ", 0.0f);
	//log_info1 = logger.addMessage("-");

	log_x1 = logger.addMessage();
	log_y1 = logger.addMessage();

	log_x2 = logger.addMessage();
	log_y2 = logger.addMessage();

	log_x3 = logger.addMessage();
	log_y3 = logger.addMessage();

	VA_Box_Lines = new VertexArray(vertices, indices, colors, 8, 24, VertexArray::Mode::LINES);
	VA_tri_line = new VertexArray(line_tri_vert, nullptr, nullptr, 6, -1, VertexArray::Mode::LINES);

	G_Box1 = new GameObject(VA_Box_Lines);
	G_Box2 = new GameObject(VA_Box_Lines);
	G_Tri = new GameObject(VA_tri_line);

	G_Box2->transform.setParent(&G_Box1->transform);

	// DEBUG
	G_Box1->transform.setPosition(Vector3(+100, +100, 0));
	G_Box2->transform.setPosition(Vector3(0, -200, 0));

	E_1 = new Emitter(50);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine or Print) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	//App::DrawLine(0, 0, 0.5f, 0.5f, 1, 0, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();

	//glClearDepth(0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Move Camera
	static float CamSpeed = 5.0f;
	if (GetAsyncKeyState('W'))
		CameraManager.getMain()->m_transform.increasePosition(Vector3(0, +CamSpeed, 0));
	if (GetAsyncKeyState('S'))
		CameraManager.getMain()->m_transform.increasePosition(Vector3(0, -CamSpeed, 0));
	if (GetAsyncKeyState('A'))
		CameraManager.getMain()->m_transform.increasePosition(Vector3(-CamSpeed, 0, 0));
	if (GetAsyncKeyState('D'))
		CameraManager.getMain()->m_transform.increasePosition(Vector3(+CamSpeed, 0, 0));

	

	//G_Box1->transform.setScale(Vector3(3, 3, 3));
	//G_Box2->transform.setScale(Vector3(3, 1, 3));

	if (GetAsyncKeyState(VK_RIGHT))
	{
		G_Box1->transform.increasePosition(Vector3(+5, 0, 0));
		G_Box1->transform.increaseRotation(Vector3(0, 0, +4));
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		G_Box1->transform.increasePosition(Vector3(-5, 0, 0));
		G_Box1->transform.increaseRotation(Vector3(0, 0, -4));
	}
	
	if (GetAsyncKeyState(VK_UP))
	{
		G_Box1->transform.increasePosition(Vector3(0, +5, 0));
		G_Box1->transform.increaseRotation(Vector3(+4, 0, 0));
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		G_Box1->transform.increasePosition(Vector3(0, -5, 0));
		G_Box1->transform.increaseRotation(Vector3(-4, 0, 0));
	}

	if (GetAsyncKeyState('Z'))
	{
		G_Tri->transform.increaseRotation(Vector3(0, 0, +4));
		G_Box1->transform.increaseRotation(Vector3(0, +4, 0));
	}
	else if (GetAsyncKeyState('X'))
	{
		G_Tri->transform.increaseRotation(Vector3(0, 0, -4));
		G_Box1->transform.increaseRotation(Vector3(0, -4, 0));
	}
	//

	if (GetAsyncKeyState(VK_SPACE))
	{
		G_Tri->transform.increasePosition(G_Tri->transform.getUp());
		G_Box1->transform.increasePosition(G_Box1->transform.getUp());
	}
	
	//G_Box2->transform.increaseRotation(Vector3(-4, 0, 3));

	//App::DrawPoint(Vector2(100, 100), Color::CYAN);

	G_Box1->draw();
	//G_Box2->draw();
	//G_Tri->draw();

	E_1->transform.setPosition(Vector3(0));
	E_1->draw();

	//G_Box1->transform.drawDirections();

	//App::DrawPoint(Vector2(200, 200), Color3F::CYAN);

	log_x1->m_message = "Cam X: " + std::to_string(CameraManager.getMain()->m_transform.getPosition().x);
	log_y1->m_message = "Cam Y: " + std::to_string(CameraManager.getMain()->m_transform.getPosition().y);

	//log_x1->m_message = "Forward X: " + std::to_string(G_Box1->transform.getForward().x);
	//log_y1->m_message = "Forward Y: " + std::to_string(G_Box1->transform.getForward().y);
	//
	//log_x2->m_message = "Up X: " + std::to_string(G_Box1->transform.getUp().x);
	//log_y2->m_message = "Up Y: " + std::to_string(G_Box1->transform.getUp().y);
	//
	//log_x3->m_message = "Right X: " + std::to_string(G_Box1->transform.getRight().x);
	//log_y3->m_message = "Right Y: " + std::to_string(G_Box1->transform.getRight().y);

	//log_val1->m_message = "ASD";
	//log_val2->m_value = 99;

	//	Vector3 P1 = Vector3(-50, -30, 0);
	//	Vector3 P2 = Vector3(50, -30, 0);
	//	Vector3 P3 = Vector3(0, 30, 0);
	//	
	//	static float angle = 0.0f;
	//	static Vector3 move = Vector3();
	//	
	//	log_tri_x->m_value = P3.x;
	//	log_tri_y->m_value = P3.y;
	//	
	//	if (GetAsyncKeyState(VK_LEFT))
	//		angle -= 1.0f;
	//	else if (GetAsyncKeyState(VK_RIGHT))
	//		angle += 1.0f;
	//	
	//	if (GetAsyncKeyState(VK_UP))
	//		move += 1.0f;
	//	else if (GetAsyncKeyState(VK_DOWN))
	//		move -= 1.0f;
	//	
	//	log_angle->m_value = angle;
	//	
	//	
	//	Transform T(move, Vector3(0, 0, angle), Vector3(1));
	//	
	//	Matrix4x4 R = T.getModel();
	//	
	//	//Matrix4x4 R = Matrix4x4::GetRotation(Degrees(angle), Vector3(0, 0, 1));
	//	
	//	P1 = R * P1;
	//	P2 = R * P2;
	//	P3 = R * P3;
	//	
	//	App::DrawLine(P1.x, P1.y, P2.x, P2.y, 1, 0, 1);
	//	App::DrawLine(P2.x, P2.y, P3.x, P3.y, 0, 1, 1);
	//	App::DrawLine(P3.x, P3.y, P1.x, P1.y, 0, 0, 1);

	logger.displayText();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{

}