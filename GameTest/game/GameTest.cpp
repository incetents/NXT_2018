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

Logger logger(5, 5, 3);

LogData<float>* log_val1;
LogData<int>* log_val2;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	//log_val1 = logger.addDataMessage("Value: ", 10.0f, Color3F::getColor(ColorIndex::PURPLE));
	//log_val2 = logger.addDataMessage("V: ", 15);
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

	logger.displayText();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{

}