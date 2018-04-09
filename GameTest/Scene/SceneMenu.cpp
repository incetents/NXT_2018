
#include "stdafx.h"
#include "SceneMenu.h"

#include "../App/app.h"
#include "../Particle/Emitter.h"
#include "../Scene/GameStateManager.h"

void SceneMenu::Init()
{
	emitter = new Emitter(100);
	emitter->setColorByLife(Color3F::RED(), Color3F::ORANGE(), Color3F::YELLOW());

	rq.add<Emitter>(emitter);

	// Init all
	rq.initAll();
}
GameState SceneMenu::Update(float delta)
{
	if (GetAsyncKeyState('1'))
		return GameState::TEST;
	if (GetAsyncKeyState('3'))
		return GameState::GAMEPLAY;

	

	if (GetAsyncKeyState(VK_RETURN))
	{
		return GameState::GAMEPLAY;
	}

	// Update all
	rq.updateAll(delta);

	return currentGameState;
}
void SceneMenu::Render()
{
	App::Print((APP_VIRTUAL_WIDTH/2) - 90, APP_VIRTUAL_HEIGHT/2, "PINBALL DEMO", Color3F::BLUE(), GLUT_BITMAP_TIMES_ROMAN_24);
	App::Print(APP_VIRTUAL_WIDTH / 2 - 100, (APP_VIRTUAL_HEIGHT / 2) - 40, "Press Enter To Play", Color3F::BLUE(), GLUT_BITMAP_TIMES_ROMAN_24);
	glPopMatrix();

	// Draw All Objects
	rq.drawAll();
}
void SceneMenu::Delete()
{
	delete emitter;
}

