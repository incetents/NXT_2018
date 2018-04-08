
#include "stdafx.h"
#include "SceneMenu.h"

#include "../Particle/Emitter.h"
#include "../Scene/GameStateManager.h"

void SceneMenu::Init()
{
	emitter = new Emitter(100);
	emitter->setColor(Color3F::RED());

	rq.add<Emitter>(emitter);

	// Init all
	rq.initAll();
}
GameState SceneMenu::Update(float delta)
{
	if (GetAsyncKeyState('2'))
		return GameState::TEST;

	// Update all
	rq.updateAll(delta);

	return currentGameState;
}
void SceneMenu::Render()
{
	// Draw All Objects
	rq.drawAll();
}
void SceneMenu::Delete()
{
	delete emitter;
}