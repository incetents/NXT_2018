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
#include "../app/SimpleLogger.h"

#include "../Math/MatrixStack.h"
#include "../math/Transform.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/CameraManager.h"
#include "../GameObject/RenderQueue.h"
#include "../Particle/Emitter.h"
#include "../Math/Vector3.h"
#include "../game/GameStateManager.h"

int ScreenWidth = APP_VIRTUAL_WIDTH;
int ScreenHeight = APP_VIRTUAL_HEIGHT;

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

GameObject* G_Box0;
GameObject* G_Box1;
GameObject* G_Box2;
GameObject* G_Box3;
GameObject* G_Box4;
GameObject* G_Box5;
GameObject* G_Tri;


Emitter* E_1;
	
//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	GameStateManager.Init();

	SLogStart(10, 10);
	SLogSpacing(20);

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

	VA_Box_Lines = new VertexArray(8, VertexArray::Mode::LINES);
	VA_Box_Lines->
		setPositions(vertices, 8)
		.setColors(colors, 8)
		.setIndices(indices, 24);

	VA_tri_line = new VertexArray(6, VertexArray::Mode::LINES);
	VA_tri_line->setPositions(line_tri_vert, 6);

	//VA_Box_Lines = new VertexArray(vertices, indices, colors, 8, 24, VertexArray::Mode::LINES);
	//VA_tri_line = new VertexArray(line_tri_vert, nullptr, nullptr, 6, -1, VertexArray::Mode::LINES);

	G_Box0 = GameObject::addGameObject(VA_Box_Lines, "NODE0");
	G_Box1 = GameObject::addGameObject(VA_Box_Lines, "NODE1");
	G_Box2 = GameObject::addGameObject(VA_Box_Lines, "NODE2");
	G_Box3 = GameObject::addGameObject(VA_Box_Lines, "NODE3");
	G_Box4 = GameObject::addGameObject(VA_Box_Lines, "NODE4");
	G_Box5 = GameObject::addGameObject(VA_Box_Lines, "NODE5");
	G_Tri  = GameObject::addGameObject(VA_tri_line,  "NODE6");

	// Parent Hierarchy 
	//G_Box0->transform.addChild(&G_Box1->transform);

	G_Box1->transform->addChild(G_Box2->transform);
	G_Box1->transform->addChild(G_Box3->transform);

	G_Box2->transform->addChild(G_Box4->transform);
	G_Box2->transform->addChild(G_Box5->transform);

	// DEBUG
	G_Box1->transform->setPosition(Vector3(0, 0, 0));
	G_Box2->transform->setPosition(Vector3(50, 0, 0));
	G_Box3->transform->setPosition(Vector3(-50, 0, 0));
	G_Box4->transform->setPosition(Vector3(0, +50, 0));
	G_Box5->transform->setPosition(Vector3(0, -50, 0));

	

	E_1 = new Emitter(45, 30);
	//E_1->setInheritVelocity(Vector3(1, 1, 0), 0.6f);

	//E_1->setColor(Color::RED);
	//E_1->setColorByLife(Color::GREEN, Color::RED);
	E_1->setColorByLife(Color::YELLOW, Color::CYAN, Color::RED);

	E_1->startEmitter();

	// Put all GameObjects in the renderQueue

	RenderQueue.add(G_Box1);
	RenderQueue.add(G_Box2);
	RenderQueue.add(G_Box3);
	RenderQueue.add(G_Box4);
	RenderQueue.add(G_Box5);
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
	SLogPrint("Node0 Child Count: " + std::to_string(G_Box0->transform->getChildCount()), Color::WHITE);
	SLogPrint("Node1 Child Count: " + std::to_string(G_Box1->transform->getChildCount()), Color::WHITE);
	SLogPrint("Node2 Child Count: " + std::to_string(G_Box2->transform->getChildCount()), Color::WHITE);
	SLogPrint("Node3 Child Count: " + std::to_string(G_Box3->transform->getChildCount()), Color::WHITE);
	SLogPrint("Node4 Child Count: " + std::to_string(G_Box4->transform->getChildCount()), Color::WHITE);
	SLogPrint("Node5 Child Count: " + std::to_string(G_Box5->transform->getChildCount()), Color::WHITE);

	Transform* Node0_Parent = G_Box0->transform->getParent();
	if (Node0_Parent == nullptr)
		SLogPrint("Node0 Has No Parent", Color::RED);
	else
		SLogPrint("Node0 Parent = " + Node0_Parent->getGameObjectReference()->name, Color::RED);

	Transform* Node1_Parent = G_Box1->transform->getParent();
	if(Node1_Parent == nullptr)
		SLogPrint("Node1 Has No Parent", Color::RED);
	else
		SLogPrint("Node1 Parent = " + Node1_Parent->getGameObjectReference()->name, Color::RED);

	Transform* Node2_Parent = G_Box2->transform->getParent();
	if (Node2_Parent == nullptr)
		SLogPrint("Node2 Has No Parent", Color::RED);
	else
		SLogPrint("Node2 Parent = " + Node2_Parent->getGameObjectReference()->name, Color::RED);

	Transform* Node3_Parent = G_Box3->transform->getParent();
	if (Node3_Parent == nullptr)
		SLogPrint("Node3 Has No Parent", Color::RED);
	else
		SLogPrint("Node3 Parent = " + Node3_Parent->getGameObjectReference()->name, Color::RED);

	Transform* Node4_Parent = G_Box4->transform->getParent();
	if (Node4_Parent == nullptr)
		SLogPrint("Node4 Has No Parent", Color::RED);
	else
		SLogPrint("Node4 Parent = " + Node4_Parent->getGameObjectReference()->name, Color::RED);

	Transform* Node5_Parent = G_Box5->transform->getParent();
	if (Node5_Parent == nullptr)
		SLogPrint("Node5 Has No Parent", Color::RED);
	else
		SLogPrint("Node5 Parent = " + Node5_Parent->getGameObjectReference()->name, Color::RED);

	
	if (GetAsyncKeyState('1'))
		E_1->play();
	if (GetAsyncKeyState('2'))
		E_1->pause();
	if (GetAsyncKeyState('3'))
		E_1->stop();

	if (GetAsyncKeyState('4'))
		E_1->setLooping(true);

	if (GetAsyncKeyState('5'))
		E_1->setLooping(false);

	//App::DrawLine(0, 0, 0.5f, 0.5f, 1, 0, 0);

	

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

	if (App::GetController(0).CheckButton(XButton::A, false))
	{
		G_Box1->transform->increasePosition(Vector3(+5, 0, 0));
		G_Box1->transform->increaseRotation(Vector3(0, 0, +4));
	}
	if (App::GetController(1).CheckButton(XButton::A, false))
	{
		G_Box1->transform->increasePosition(Vector3(-5, 0, 0));
		G_Box1->transform->increaseRotation(Vector3(0, 0, -4));
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		G_Box1->transform->increasePosition(Vector3(+5, 0, 0));
		G_Box1->transform->increaseRotation(Vector3(0, 0, +4));
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		G_Box1->transform->increasePosition(Vector3(-5, 0, 0));
		G_Box1->transform->increaseRotation(Vector3(0, 0, -4));
	}
	
	if (GetAsyncKeyState(VK_UP))
	{
		G_Box1->transform->increasePosition(Vector3(0, +5, 0));
		G_Box1->transform->increaseRotation(Vector3(+4, 0, 0));
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		G_Box1->transform->increasePosition(Vector3(0, -5, 0));
		G_Box1->transform->increaseRotation(Vector3(-4, 0, 0));
	}

	if (GetAsyncKeyState('Z'))
	{
		G_Tri->transform->increaseRotation(Vector3(0, 0, +4));
		G_Box1->transform->increaseRotation(Vector3(0, +4, 0));
	}
	else if (GetAsyncKeyState('X'))
	{
		G_Tri->transform->increaseRotation(Vector3(0, 0, -4));
		G_Box1->transform->increaseRotation(Vector3(0, -4, 0));
	}
	//

	if (GetAsyncKeyState(VK_SPACE))
	{
		G_Tri->transform->increasePosition(G_Tri->transform->getUp() * 4.0f);
		G_Box1->transform->increasePosition(G_Box1->transform->getUp());
	}
	
	//G_Box2->transform.increaseRotation(Vector3(-4, 0, 3));

	//App::DrawPoint(Vector2(100, 100), Color::CYAN);

	//	G_Box1->draw();
	//	G_Box1->transform.drawDirections();
	//	G_Box2->draw();
	//	G_Box3->draw();
	//	G_Box4->draw();
	//	G_Box5->draw();
	//G_Tri->draw();

	//E_1->update();
	//E_1->draw();

	// Draw All GameObjects
	RenderQueue.drawAll();
	
	// Draw all text from logger
	SLogDraw;
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{

}