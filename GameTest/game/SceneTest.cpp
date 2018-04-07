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

#include "SceneTest.h"

int ScreenWidth = APP_VIRTUAL_WIDTH;   // 1024
int ScreenHeight = APP_VIRTUAL_HEIGHT; // 768

GameObject* G_Box0;
GameObject* G_Box1;
GameObject* G_Box2;
GameObject* G_Box3;
GameObject* G_Box4;
GameObject* G_Box5;
GameObject* G_Tri;

Emitter* E_1;

void SceneTest::Init()
{
	// Emitter
	Emitter* E = new Emitter(100);
	E->setColorByLife(Color3F::RED(), Color3F::ORANGE(), Color3F::YELLOW());

	// Create Ball
	ball = GameObject::createGameObject(SimpleShapes.v_circle, "Ball");
	ball->AddComponent(new Rigidbody2D(ball->transform));
	ball->GetComponent<Rigidbody2D>()->setGravityAmount(0.3f);
	ball->GetComponent<Rigidbody2D>()->setVelocity(Vec2(8.0f, 0.0f));

	ball->AddComponent(new CircleCollider2D(ball->transform));
	ball->GetComponent<Transform>()->setScale(80.0f);

	Vector2 WallPoints[] =
	{
		Vector2(-500, -150),
		Vector2(-250, -300),
		Vector2(+250, -300),
		Vector2(+500, -150),
		Vector2(+500, +150),
		Vector2(+250, +300),
		Vector2(-250, +300),
		Vector2(-500, +150),

		Vector2(-500, -150)
	};


	for (int i = 0; i < 8; i++)
	{
		// Create Wall
		VertexArray* V_Wall1 = new VertexArray(2, VertexArray::LINES);
		Vector3 V_Wall1_P[] =
		{
			Vector3(WallPoints[i]),
			Vector3(WallPoints[i + 1])
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
		W1->GetComponent<LineCollider2D>()->setPoints(WallPoints[i], WallPoints[i + 1]);
		walls.push_back(W1);
	}

	// Add Circle Ball for testing
	GameObject* ball_test = GameObject::createGameObject(SimpleShapes.v_circle);
	ball_test->AddComponent<>(new CircleCollider2D(ball_test->transform));
	ball_test->GetComponent<Transform>()->setPosition(Vec2(0, -100));
	ball_test->GetComponent<Transform>()->setScale(25.0f);
	walls.push_back(ball_test);

	//	// Create Wall
	//	VertexArray* V_Wall1 = new VertexArray(2, VertexArray::LINES);
	//	Vector3 V_Wall1_P[] =
	//	{
	//		Vector3(-250, -300, 0),
	//		Vector3(250, -200, 0)
	//	};
	//	Color3F V_Wall1_C[] =
	//	{
	//		Color3F::RED(),
	//		Color3F::BLUE()
	//	};
	//	V_Wall1->setPositions(V_Wall1_P, 2);
	//	V_Wall1->setColors(V_Wall1_C, 2);
	//	
	//	GameObject* W1 = GameObject::createGameObject(V_Wall1);
	//	W1->AddComponent(new LineCollider2D(W1->transform));
	//	W1->GetComponent<LineCollider2D>()->setPoints(Vector2(-250, -300), Vector2(250, -200));
	//	data.walls.push_back(W1);

	// Add GameObjects to render queue
	rq.add(ball);
	
	size_t totalWalls = walls.size();
	for (size_t i = 0; i < totalWalls; i++)
		rq.add(walls[i]);

	// Add Emitter
	//data.rq_testscene.add(E);
}
void SceneTest::Update(float delta)
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
	int total_walls = walls.size();
	for (int i = 0; i < total_walls; i++)
	{
		auto C = walls[i]->GetComponent<LineCollider2D>();
		if (C == nullptr)
			continue;

		if (ball->GetComponent<CircleCollider2D>()->checkCollision(*C))
		{
			SimpleLogger.Print("COLLISION");
			ball->GetComponent<CircleCollider2D>()->collisionResponse(*C);
		}
	}

	static float speed = 2.0f;

	if (GetAsyncKeyState(VK_UP))
		ball->transform->increasePosition(Vector2(0, +speed));
	if (GetAsyncKeyState(VK_DOWN))
		ball->transform->increasePosition(Vector2(0, -speed));
	if (GetAsyncKeyState(VK_RIGHT))
		ball->transform->increasePosition(Vector2(+speed, 0));
	if (GetAsyncKeyState(VK_LEFT))
		ball->transform->increasePosition(Vector2(-speed, 0));


	// Update All Objects
	rq.updateAll(delta);
}
void SceneTest::Render()
{
	// Draw Collision Boxes of Circles
	int total_walls = walls.size();
	for (int i = 0; i < total_walls; i++)
	{
		//data.ball->GetComponent<CircleCollider2D>()->DrawOutline();

		//data.ball->GetComponent<CircleCollider2D>()->checkCollision(*data.walls[i]->GetComponent<LineCollider2D>());
	}

	// Draw All Objects
	rq.drawAll();
}
void SceneTest::Delete()
{

}