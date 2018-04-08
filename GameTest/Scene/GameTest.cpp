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
	
#include "GameStateManager.h"

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	// Setup Simple Logger
	SLogStart(10, 10);
	SLogSpacing(20);

	// Default Hints
	App::CullMode(CullType::COUNTER_CLOCKWISE);

	// Initial State
	GameStateManager.changeState(GameStateManager::TEST);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	// Update Current Game State
	GameStateManager.Update(deltaTime);

	// Update Time
	GameStateManager.m_Time += deltaTime;
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine or Print) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	// Render Current Game State
	GameStateManager.Render();

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