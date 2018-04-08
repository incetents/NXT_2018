#pragma once

#include <vector>

#include "../Utility/Singleton.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/RenderQueue.h"
#include "../Particle/Emitter.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneGameplay.h"
#include "../Scene/SceneMenu.h"
#include "../Scene/SceneTest.h"

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
	
	};
	GameState	m_currentState = GameState::NONE;
	Scene* scene = nullptr;
	
	// Function Pointers
	//	void (GameStateManager::*Initfunction)(void) = &GameStateManager::null;
	//	void (GameStateManager::*UpdateFunction)(float) = &GameStateManager::nullf;
	//	void (GameStateManager::*RenderFunction)(void) = &GameStateManager::null;
	//	
	//	void null(){}
	//	void nullf(float) {}
	//	
	//	void InitTest();
	//	void InitMenu();
	//	void InitGameplay();
	//	
	//	void UpdateTest(float delta);
	//	void UpdateMenu(float delta);
	//	void UpdateGameplay(float delta);
	//	
	//	void RenderTest();
	//	void RenderMenu();
	//	void RenderGameplay();

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

		// Delete existing scene
		if (scene != nullptr)
		{
			// Delete function called
			scene->Delete();

			delete scene;
			scene = nullptr;
		}

		// Update Scene
		switch (m_currentState)
		{
		case GameState::TEST:
			scene = new SceneTest();
			break;

		case GameState::MENU:
			break;

		case GameState::GAMEPLAY:
			break;
		}

		if (SceneChange)
		{
			if (scene != nullptr)
				scene->Init();
		}
	}

	void Update(float delta)
	{
		if (scene != nullptr)
			scene->Update(delta);
	}

	void Render()
	{
		if (scene != nullptr)
			scene->Render();
	}


} &GameStateManager = Singleton<class GameStateManager>::instanceRef;