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
#include "../Collision/OBB.h"
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

	// Add Bumper
	Bumper* bumper1 = new Bumper("Bumper1", Bumper::Side::LEFT, 0.0f, -45.0f, Vec2(-220, -320), Vec2(130, 40));
	Bumper* bumper2 = new Bumper("Bumper2", Bumper::Side::RIGHT, 0.0f, +45.0f, Vec2(+220, -320), Vec2(130, 40));
	bumpers.push_back(bumper1);
	bumpers.push_back(bumper2);

	// Add Circle Ball for testing
	Bouncer* bouncer = new Bouncer("Bouncer1", 150.0f, Vec2(0, -300));
	bouncers.push_back(bouncer);

	
	// Add GameObjects to render queue
	rq.add<GameObject>(ball);

	size_t totalBumpers = bumpers.size();
	for (size_t i = 0; i < totalBumpers; i++)
		rq.add<GameObject>(bumpers[i]);

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


	if (GetAsyncKeyState(VK_SPACE))
	{
		bumpers[0]->Action();
		bumpers[1]->Action();
	}

	//static float speed = 2.0f;
	//
	//if (GetAsyncKeyState(VK_UP))
	//	ball->transform->increasePosition(Vector2(0, +speed));
	//if (GetAsyncKeyState(VK_DOWN))
	//	ball->transform->increasePosition(Vector2(0, -speed));
	//if (GetAsyncKeyState(VK_RIGHT))
	//	ball->transform->increasePosition(Vector2(+speed, 0));
	//if (GetAsyncKeyState(VK_LEFT))
	//	ball->transform->increasePosition(Vector2(-speed, 0));


	// Update All Objects
	rq.updateAll(delta);

	return currentGameState;
}
void SceneTest::Render()
{
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