#pragma once

#include <vector>

#include "../Utility/Singleton.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/RenderQueue.h"
#include "../Particle/Emitter.h"

static class GameStateManager : public Singleton<class GameStateManager>
{
private:

public:
	enum GameState
	{
		NONE = -1,
		TEST = 0,
		MENU,
		GAMEPLAY,
		TOTAL
	};
	struct GlobalData
	{
		RenderQueue rq_testscene;
		RenderQueue rq_menuscene;
		RenderQueue rq_gameplayscene;
		GameObject* ball;
		std::vector<GameObject*> walls;
	};
	GameState	m_currentState = GameState::NONE;
	
	// Function Pointers
	void (GameStateManager::*Initfunction)(void) = &GameStateManager::null;
	void (GameStateManager::*UpdateFunction)(float) = &GameStateManager::nullf;
	void (GameStateManager::*RenderFunction)(void) = &GameStateManager::null;

	void null(){}
	void nullf(float) {}

	void InitTest();
	void InitMenu();
	void InitGameplay();

	void UpdateTest(float delta);
	void UpdateMenu(float delta);
	void UpdateGameplay(float delta);

	void RenderTest();
	void RenderMenu();
	void RenderGameplay();

public:
	GlobalData data;
	float m_Time = 0.0f;

	const GameState& getState() const
	{
		return m_currentState;
	}
	void changeState(GameState state)
	{
		// Error States
		if (state == GameState::NONE || state == GameState::TOTAL)
			return;

		bool SceneChange = (m_currentState != state);
		m_currentState = state;

		// Set Update Function
		switch (m_currentState)
		{
		case GameState::TEST:
			Initfunction = &GameStateManager::InitTest;
			UpdateFunction = &GameStateManager::UpdateTest;
			RenderFunction = &GameStateManager::RenderTest;
			break;

		case GameState::MENU:
			Initfunction = &GameStateManager::InitMenu;
			UpdateFunction = &GameStateManager::UpdateMenu;
			RenderFunction = &GameStateManager::RenderMenu;
			break;

		case GameState::GAMEPLAY:
			Initfunction = &GameStateManager::InitGameplay;
			UpdateFunction = &GameStateManager::UpdateGameplay;
			RenderFunction = &GameStateManager::RenderGameplay;
			break;
		}

		if (SceneChange)
		{
			// Run Init Function
			(this->*Initfunction)();
		}
	}

	void Update(float delta)
	{
		// Run Update Function
		(this->*UpdateFunction)(delta);
	}

	void Render()
	{
		// Run Render Function
		(this->*RenderFunction)();
	}


} &GameStateManager = Singleton<class GameStateManager>::instanceRef;