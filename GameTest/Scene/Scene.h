#pragma once

#include "../GameObject/RenderQueue.h"

enum class GameState
{
	NONE = -1,
	TEST = 0,
	MENU,
	GAMEPLAY,
	TOTAL
};

class Scene
{
protected:
	// Current State
	const GameState currentGameState = GameState::NONE;
	RenderQueue rq; // Render Stuff
public:

	// Creation
	Scene(GameState newstate) : currentGameState(newstate) {}

	// States
	virtual void Init() = 0;
	virtual GameState Update(float delta) = 0;
	virtual void Render() = 0;
	virtual void Delete()
	{
		// Empty rq
		rq.clear();
	}
};