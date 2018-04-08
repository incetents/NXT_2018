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
#include "../Scene/GameStateManager.h"
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
	ball = new Ball("Ball", 60.0f, Vec2(-400, -100), Vec2(12.0f, 1.0f));
	ball->renderer->m_lineWidth = 4.0f;
	ball->GetComponent<Rigidbody2D>()->setGravityAmount(0.9f);

	// Create Bumper
	Vector2 WallPoints[] =
	{
		Vector2(-250, -300),
		Vector2(+250, -300),
		Vector2(+500, -150),
		Vector2(+500, +150),
		Vector2(+250, +300),
		Vector2(-250, +300),
		Vector2(-500, +150),
		Vector2(-500, -150),

		Vector2(-250, -300)
	};

	for (int i = 0; i < 8; i++)
	{
		Wall* NewWall = new Wall(
			"Wall: " + toString(i),
			WallPoints[i],
			WallPoints[i + 1],
			Color3F::RED(),
			Color3F::BLUE()
		);

		walls.push_back(NewWall);
	}

	// Add Circle Ball for testing
	Bouncer* bouncer = new Bouncer("Bouncer1", 150.0f, Vec2(0, -300));

	//GameObject* ball_test = new GameObject(SimpleShapes.v_circle);
	//ball_test->AddComponent<>(new CircleCollider2D(ball_test->transform));
	//ball_test->GetComponent<Transform>()->setPosition(Vec2(0, -300));
	//ball_test->GetComponent<Transform>()->setScale(150.0f);
	bouncers.push_back(bouncer);

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
	rq.add<GameObject>(ball);

	size_t totalWalls = walls.size();
	for (size_t i = 0; i < totalWalls; i++)
		rq.add<GameObject>(walls[i]);

	size_t totalBouncers = bouncers.size();
	for (size_t i = 0; i < totalBouncers; i++)
		rq.add<GameObject>(bouncers[i]);

	// Add Emitter
	//data.rq_testscene.add(E);

	// Init everything in RenderQueue
	rq.initAll();

}
GameState SceneTest::Update(float delta)
{
	if (GetAsyncKeyState('1'))
	{
		return GameState::MENU;
		//ball->GetComponent<Rigidbody2D>()->addForce(Vec2(0, 1));
		//return;
	}

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
	size_t total_walls = walls.size();
	for (int i = 0; i < total_walls; i++)
	{
		// Ball Collides with line
		auto L = walls[i]->GetComponent<LineCollider2D>();
		if (L != nullptr && ball->GetComponent<CircleCollider2D>()->checkCollision(*L))
		{
			SimpleLogger.Print("COLLISION LINE");
			ball->GetComponent<CircleCollider2D>()->collisionResponse(*L);
		}
	}

	size_t total_bouncers = bouncers.size();
	for (int i = 0; i < total_bouncers; i++)
	{
		// Ball colliders with circles
		auto C = bouncers[i]->GetComponent<CircleCollider2D>();
		if (C != nullptr && ball->GetComponent<CircleCollider2D>()->checkCollision(*C))
		{
			SimpleLogger.Print("COLLISION CIRCLE");
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

	return currentGameState;
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
	delete ball;
	for (int i = 0; i < walls.size(); i++)
	{
		delete walls[i];
	}
	walls.clear();
}