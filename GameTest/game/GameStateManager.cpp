
#include "GameStateManager.h"

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
#include "../Collision/LineCollider.h"
#include "../Collision/Rigidbody.h"
#include "../Collision/AABB.h"
#include "../Collision/Circle.h"
#include "../Math/SimpleShapes.h"

int ScreenWidth = APP_VIRTUAL_WIDTH;
int ScreenHeight = APP_VIRTUAL_HEIGHT;

GameObject* G_Box0;
GameObject* G_Box1;
GameObject* G_Box2;
GameObject* G_Box3;
GameObject* G_Box4;
GameObject* G_Box5;
GameObject* G_Tri;

Emitter* E_1;

void GameStateManager::InitTest()
{
	// Emitter
	Emitter* E = new Emitter(100);
	E->setColorByLife(Color3F::RED(), Color3F::ORANGE(), Color3F::YELLOW());
	E->startEmitter();

	// Create Ball
	data.ball = GameObject::createGameObject(SimpleShapes.v_circle, "Ball");
	data.ball->AddComponent(new Rigidbody(data.ball->transform));
	data.ball->GetComponent<Rigidbody>()->setGravityAmount(0.2f);

	data.ball->AddComponent(new CircleCollider2D(data.ball->transform));
	data.ball->GetComponent<Transform>()->setScale(10.0f);

	// Create Wall
	VertexArray* V_Wall1 = new VertexArray(2, VertexArray::LINES);
	Vector3 V_Wall1_P[] =
	{
		Vector3(-220, -100, 0),
		Vector3(+220, -100, 0)
	};
	Color3F V_Wall1_C[] =
	{
		Color3F::RED(),
		Color3F::BLUE()
	};
	V_Wall1->setPositions(V_Wall1_P, 2);
	V_Wall1->setColors(V_Wall1_C, 2);

	GameObject* W1 = GameObject::createGameObject(V_Wall1);
	W1->AddComponent(new LineCollider2D(W1->transform));
	W1->GetComponent<LineCollider2D>()->setPoints(Vec2(-220, -100), Vec2(+220, -100));
	data.walls.push_back(W1);

	// Add GameObjects to render queue
	data.rq_testscene.add(data.ball);

	size_t totalWalls = data.walls.size();
	for (size_t i = 0; i < totalWalls; i++)
		data.rq_testscene.add(data.walls[i]);

	// Add Emitter
	data.rq_testscene.add(E);

	/*
	//G_Box0 = GameObject::createGameObject(VA_Box_Lines, "NODE0");
	G_Box1 = GameObject::createGameObject(SimpleShapes.v_box, "NODE1");
	G_Box2 = GameObject::createGameObject(SimpleShapes.v_box, "NODE2");
	G_Box3 = GameObject::createGameObject(SimpleShapes.v_box, "NODE3");
	G_Box4 = GameObject::createGameObject(SimpleShapes.v_box, "NODE4");
	G_Box5 = GameObject::createGameObject(SimpleShapes.v_box, "NODE5");

	G_Box1->transform->setScale(25.0f);
	data.ball->transform->setScale(50.0f);

	// Parent Hierarchy 
	//G_Box0->transform.addChild(&G_Box1->transform);

	G_Box1->transform->addChild(G_Box2->transform);
	G_Box1->transform->addChild(G_Box3->transform);

	G_Box2->transform->addChild(G_Box4->transform);
	G_Box2->transform->addChild(G_Box5->transform);

	// DEBUG
	G_Box1->transform->setPosition(Vector3(0, 0, 0));
	G_Box2->transform->setPosition(Vector3(2, 0, 0));
	G_Box3->transform->setPosition(Vector3(-2, 0, 0));
	G_Box4->transform->setPosition(Vector3(0, +2, 0));
	G_Box5->transform->setPosition(Vector3(0, -2, 0));

	G_Box1->AddComponent<Rigidbody>(new Rigidbody(G_Box1));
	G_Box1->GetComponent<Rigidbody>()->setGameObjectReference(G_Box1);

	E_1 = new Emitter(45, 30);
	//E_1->setInheritVelocity(Vector3(1, 1, 0), 0.6f);

	//E_1->setColor(Color::RED);
	//E_1->setColorByLife(Color::GREEN, Color::RED);
	E_1->setColorByLife(Color3F::YELLOW(), Color3F::CYAN(), Color3F::RED());

	E_1->startEmitter();

	// Put all GameObjects in the renderQueue

	//RenderQueue.add(G_Box1);
	//RenderQueue.add(G_Box2);
	//RenderQueue.add(G_Box3);
	//RenderQueue.add(G_Box4);
	//RenderQueue.add(G_Box5);
	data.rq_testscene.add(G_Tri);

	//RenderQueue.add(E_1);

	G_Box1->AddComponent(new CircleCollision());
	//G_Box1->AddComponent(new LineCollider2D());
	//G_Box1->GetComponent<LineCollider2D>()->m_p1 = Vec2(0, 0);
	//G_Box1->GetComponent<LineCollider2D>()->m_p2 = Vec2(100, 100);
	*/
}
void GameStateManager::UpdateTest(float delta)
{
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

	// Collision Test
	int total_walls = data.walls.size();
	for (int i = 0; i < total_walls; i++)
	{
		auto C = *data.walls[i]->GetComponent<LineCollider2D>();

		if (data.ball->GetComponent<CircleCollider2D>()->checkCollision(C))
		{
			data.ball->GetComponent<CircleCollider2D>()->collisionResponse(C);
		}
	}

	//	SLogPrint("Node0 Child Count: " + std::to_string(G_Box0->transform->getChildCount()), Color::WHITE);
	//	SLogPrint("Node1 Child Count: " + std::to_string(G_Box1->transform->getChildCount()), Color::WHITE);
	//	SLogPrint("Node2 Child Count: " + std::to_string(G_Box2->transform->getChildCount()), Color::WHITE);
	//	SLogPrint("Node3 Child Count: " + std::to_string(G_Box3->transform->getChildCount()), Color::WHITE);
	//	SLogPrint("Node4 Child Count: " + std::to_string(G_Box4->transform->getChildCount()), Color::WHITE);
	//	SLogPrint("Node5 Child Count: " + std::to_string(G_Box5->transform->getChildCount()), Color::WHITE);
	//	
	//	Transform* Node0_Parent = G_Box0->transform->getParent();
	//	if (Node0_Parent == nullptr)
	//		SLogPrint("Node0 Has No Parent", Color::RED);
	//	else
	//		SLogPrint("Node0 Parent = " + Node0_Parent->getGameObjectReference()->name, Color::RED);
	//	
	//	Transform* Node1_Parent = G_Box1->transform->getParent();
	//	if (Node1_Parent == nullptr)
	//		SLogPrint("Node1 Has No Parent", Color::RED);
	//	else
	//		SLogPrint("Node1 Parent = " + Node1_Parent->getGameObjectReference()->name, Color::RED);
	//	
	//	Transform* Node2_Parent = G_Box2->transform->getParent();
	//	if (Node2_Parent == nullptr)
	//		SLogPrint("Node2 Has No Parent", Color::RED);
	//	else
	//		SLogPrint("Node2 Parent = " + Node2_Parent->getGameObjectReference()->name, Color::RED);
	//	
	//	Transform* Node3_Parent = G_Box3->transform->getParent();
	//	if (Node3_Parent == nullptr)
	//		SLogPrint("Node3 Has No Parent", Color::RED);
	//	else
	//		SLogPrint("Node3 Parent = " + Node3_Parent->getGameObjectReference()->name, Color::RED);
	//	
	//	Transform* Node4_Parent = G_Box4->transform->getParent();
	//	if (Node4_Parent == nullptr)
	//		SLogPrint("Node4 Has No Parent", Color::RED);
	//	else
	//		SLogPrint("Node4 Parent = " + Node4_Parent->getGameObjectReference()->name, Color::RED);
	//	
	//	Transform* Node5_Parent = G_Box5->transform->getParent();
	//	if (Node5_Parent == nullptr)
	//		SLogPrint("Node5 Has No Parent", Color::RED);
	//	else
	//		SLogPrint("Node5 Parent = " + Node5_Parent->getGameObjectReference()->name, Color::RED);

	/*
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
	*/

	//G_Box1->transform.setScale(Vector3(3, 3, 3));
	//G_Box2->transform.setScale(Vector3(3, 1, 3));

	/*
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
	*/

	// Update All Objects
	data.rq_testscene.updateAll(delta);

}
void GameStateManager::RenderTest()
{
	// Draw Collisin Boxes
	int total_walls = data.walls.size();
	for (int i = 0; i < total_walls; i++)
	{
		data.ball->GetComponent<CircleCollider2D>()->Draw();
	}

	// Draw All Objects
	data.rq_testscene.drawAll();
}

void GameStateManager::InitMenu()
{

}
void GameStateManager::UpdateMenu(float delta)
{
	data.rq_menuscene.updateAll(delta);
}
void GameStateManager::RenderMenu()
{
	data.rq_menuscene.drawAll();
}

void GameStateManager::InitGameplay()
{
	
}
void GameStateManager::UpdateGameplay(float delta)
{
	data.rq_gameplayscene.updateAll(delta);
}
void GameStateManager::RenderGameplay()
{
	data.rq_gameplayscene.drawAll();
}