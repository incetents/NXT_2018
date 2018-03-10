//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <iostream>
//------------------------------------------------------------------------
#include "../app\app.h"
#include "../app\main.h"
#include "../app\Logger.h"

#include "../math/Transform.h"

Logger logger(5, 5, 3);

LogData<float>* log_angle;
LogData<float>* log_tri_x;
LogData<float>* log_tri_y;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	log_angle = logger.addDataMessage("Angle: ", 0.0f, Color3F::getColor(ColorIndex::PURPLE));
	log_tri_x = logger.addDataMessage("X: ", 0.0f);
	log_tri_y = logger.addDataMessage("Y: ", 0.0f);
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
	App::DrawLine(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1, 0, 0);

	//log_val1->m_message = "ASD";
	//log_val2->m_value = 99;

	Vector3 P1 = Vector3(-50, -30, 0);
	Vector3 P2 = Vector3(50, -30, 0);
	Vector3 P3 = Vector3(0, 30, 0);

	static float angle = 0.0f;
	static Vector3 move = Vector3();

	log_tri_x->m_value = P3.x;
	log_tri_y->m_value = P3.y;

	if (GetAsyncKeyState(VK_LEFT))
		angle -= 1.0f;
	else if (GetAsyncKeyState(VK_RIGHT))
		angle += 1.0f;

	if (GetAsyncKeyState(VK_UP))
		move += 1.0f;
	else if (GetAsyncKeyState(VK_DOWN))
		move -= 1.0f;

	log_angle->m_value = angle;


	Transform T(move, Vector3(0, 0, angle), Vector3(1));

	Matrix4x4 R = T.getModel();

	//Matrix4x4 R = Matrix4x4::GetRotation(Degrees(angle), Vector3(0, 0, 1));

	P1 = R * P1;
	P2 = R * P2;
	P3 = R * P3;

	App::DrawLine(P1.x, P1.y, P2.x, P2.y, 1, 0, 1);
	App::DrawLine(P2.x, P2.y, P3.x, P3.y, 0, 1, 1);
	App::DrawLine(P3.x, P3.y, P1.x, P1.y, 0, 0, 1);

	logger.displayText();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{

}