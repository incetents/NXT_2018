
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

#include "../game/Ball.h"
#include "../game/Flipper.h"
#include "../game/Wall.h"
#include "../game/Bouncer.h"

#include "SceneGameplay.h"

static Vec2 ballSpawnPosition = Vec2(0, -50.0f);

void SceneGameplay::Init()
{
	// Create Ball
	ball = new Ball("Ball", 60.0f, ballSpawnPosition, Vec2(0.0f, 0.0f));
	ball->renderer->m_lineWidth = 4.0f;
	ball->GetComponent<Rigidbody2D>()->setGravityAmount(0.9f);

	// Arrow effect
	Vector3 Arrow_positions[] =
	{
		// Line 1
		Vector3(0, 80, 0),
		Vector3(0, 200, 0),
		// Line 2
		Vector3(-80, 150, 0),
		Vector3(0, 200, 0),
		// Line 3
		Vector3(+80, 150, 0),
		Vector3(0, 200, 0)
	};
	Color3F Arrow_colors[] =
	{
		Color3F::RED(),
		Color3F::RED(),
		Color3F::RED(),
		Color3F::RED(),
		Color3F::RED(),
		Color3F::RED()
	};
	VertexArray* v_arrows = new VertexArray(6, VertexArray::Mode::LINES);
	v_arrows->setPositions(Arrow_positions, 6);
	v_arrows->setColors(Arrow_colors, 6);
	arrow = new GameObject(v_arrows, "Arrow");
	arrow->transform->setPosition(ball->transform->getPosition());

	// Create Walls
	float y_offset = -360.0f;
	int wallCount = 10;
	Vector2 WallPoints[] =
	{
		// Bottom Section of map
		Vector2(-500, 300 + y_offset),
		Vector2(-160, 60 + y_offset),
		Vector2(-160, -1000 + y_offset),
		Vector2(+160, -1000 + y_offset),
		Vector2(+160, 60 + y_offset),
		Vector2(+500, 300 + y_offset),
		// top part
		Vector2(+500, 1200 + y_offset),
		Vector2(+240, 1350 + y_offset),
		Vector2(-240, 1350 + y_offset),
		Vector2(-500, 1200 + y_offset),
	};

	for (int i = 0; i < wallCount; i++)
	{
		int indexNext = (i + 1) % wallCount;

		Wall* NewWall = new Wall(
			"Wall: " + toString(i),
			WallPoints[i],
			WallPoints[indexNext],
			Color3F::RED(),
			Color3F::BLUE()
		);
		NewWall->setThickness(8.0f);

		walls.push_back(NewWall);
	}

	// Add Flippers
	Flipper* bumper1 = new Flipper("Flipper1", Flipper::Side::LEFT, +45.0f, -45.0f, Vec2(-160, 55 + y_offset), Vec2(130, 40));//320
	Flipper* bumper2 = new Flipper("Flipper2", Flipper::Side::RIGHT, -45.0f, +45.0f, Vec2(+160, 55 + y_offset), Vec2(130, 40));
	bumpers.push_back(bumper1);
	bumpers.push_back(bumper2);

	// AddBouncers
	int BouncerCount = 5;
	Vector3 BouncersToAdd[] =
	{
		Vec3(0, 1000 + y_offset, 120.0f),
		Vec3(-290, 800 + y_offset, 120.0f),
		Vec3(+290, 800 + y_offset, 120.0f),
		Vec3(-400, 500 + y_offset, 120.0f),
		Vec3(+400, 500 + y_offset, 120.0f)
	};
	for (int i = 0; i < BouncerCount; i++)
	{
		Bouncer* bouncer = new Bouncer("Bouncer1", BouncersToAdd[i].z, Vector2(BouncersToAdd[i]));
		bouncers.push_back(bouncer);
	}

	// send everything to the renderqueue
	rq.add<GameObject>(ball);
	rq.add<GameObject>(arrow);

	size_t totalBumpers = bumpers.size();
	size_t totalWalls = walls.size();
	size_t totalBouncers = bouncers.size();

	for (size_t i = 0; i < totalBumpers; i++)
		rq.add<GameObject>(bumpers[i]);

	for (size_t i = 0; i < totalWalls; i++)
		rq.add<GameObject>(walls[i]);

	for (size_t i = 0; i < totalBouncers; i++)
		rq.add<GameObject>(bouncers[i]);

	// Init everything in RenderQueue
	rq.initAll();
}
GameState SceneGameplay::Update(float delta)
{
	// Change scene (debug)
	if (GetAsyncKeyState('1'))
		return GameState::TEST;
	if (GetAsyncKeyState('2'))
		return GameState::MENU;

	// Ball Spawn
	if (ballSpawn)
	{
		ball->transform->setPosition(ballSpawnPosition);
		ball->GetComponent<Rigidbody2D>()->setActive(false);
		arrow->setActive(true);
		arrow->transform->setRotationZ(sinf(GameStateManager.time * 0.008f) * 80.0f);

		// Start Ball moving around
		if (GetAsyncKeyState(VK_SPACE))
		{
			ballSpawn = false;
			ball->transform->setPosition(ballSpawnPosition);
			Vec2 Aim = Vec2(0, 1).Rotate(-Radians(arrow->transform->getRotation().z));
			ball->GetComponent<Rigidbody2D>()->setActive(true);
			ball->GetComponent<Rigidbody2D>()->setVelocity(Vec2(0, 0));
			ball->GetComponent<Rigidbody2D>()->addForce(Aim * 40.0f);
		}
		//CameraManager.getMain()->m_transform.setY(ballSpawnPosition.y);
	}
	else
	{
		arrow->setActive(false);
		ball->GetComponent<Rigidbody2D>()->setActive(true);
	}

	// Move Camera Y to ball
	float game_y = ball->transform->getPosition().y;
	game_y = MacroClamp(game_y, -90, 600);

	CameraManager.getMain()->m_transform.setY(game_y);

	// Action
	if (GetAsyncKeyState(VK_UP))
	{
		bumpers[0]->Action();
		bumpers[1]->Action();
	}
	if (GetAsyncKeyState(VK_LEFT))
		bumpers[0]->Action();
	if (GetAsyncKeyState(VK_RIGHT))
		bumpers[1]->Action();

	// Death possibility
	if (ball->transform->getPosition().y < -500 ||
		ball->transform->getPosition().y > 1500 ||
		ball->transform->getPosition().y != ball->transform->getPosition().y // floating point error
		)
	{
		SimpleLogger.Print("RESET");
		ballSpawn = true;
	}

#if _DEBUG
	SimpleLogger.Print("Ball Pos: " + toString(ball->transform->getPosition().x) + "|" + toString(ball->transform->getPosition().y));
#endif

	// Update objects
	rq.updateAll(delta);

	// Move Camera
	//static float CamSpeed = 25.0f;
	//if (GetAsyncKeyState('W'))
	//	CameraManager.getMain()->m_transform.increasePosition(Vector3(0, +CamSpeed, 0));
	//if (GetAsyncKeyState('S'))
	//	CameraManager.getMain()->m_transform.increasePosition(Vector3(0, -CamSpeed, 0));

	return currentGameState;
}
void SceneGameplay::Render()
{
	// Screen Text
	if (ballSpawn)
	{
		std::string msg1 = "Press Spacebar to launch the ball";
		std::string msg2 = "Press Left/Right/Up to use the flippers";
		App::Print((APP_VIRTUAL_WIDTH / 2) - 170, (APP_VIRTUAL_HEIGHT / 2) - 70, msg1.c_str(), Color3F::BLUE(), GLUT_BITMAP_TIMES_ROMAN_24);
		App::Print((APP_VIRTUAL_WIDTH / 2) - 185, (APP_VIRTUAL_HEIGHT / 2) - 110, msg2.c_str(), Color3F::BLUE(), GLUT_BITMAP_TIMES_ROMAN_24);
	}

	// Render objects
	rq.drawAll();
}
void SceneGameplay::Delete()
{
	delete ball;

	size_t totalBumpers = bumpers.size();
	for (size_t i = 0; i < totalBumpers; i++)
		delete bumpers[i];

	size_t totalWalls = walls.size();
	for (size_t i = 0; i < totalWalls; i++)
		delete walls[i];

	size_t totalBouncers = bouncers.size();
	for (size_t i = 0; i < totalBouncers; i++)
		delete bouncers[i];
}