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
#include "../GameObject/CameraManager.h"
#include "../Math/Transform.h"

static class GameStateManager : public Singleton<class GameStateManager>
{
public:
	struct GlobalData
	{
		// Values that can be accesed from all scenes

	};
	GameState	m_currentState = GameState::NONE;
	Scene* scene = nullptr;

public:
	GlobalData  data;
	float		time = 0.0f;

	const GameState& getState() const
	{
		return m_currentState;
	}
	void changeState(GameState state)
	{
		// Error or Same States
		if (state == GameState::NONE ||
			state == GameState::TOTAL ||
			state == m_currentState
			)
			return;

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
			scene = new SceneTest(GameState::TEST);
			break;

		case GameState::MENU:
			scene = new SceneMenu(GameState::MENU);
			break;

		case GameState::GAMEPLAY:
			scene = new SceneGameplay(GameState::GAMEPLAY);
			break;
		}

		// Reset Camera
		CameraManager.getMain()->m_transform.setPosition(Vec3(0, 0, 0));

		// Call Init Function
		if (scene != nullptr)
			scene->Init();
	}

	void Update(float delta)
	{
		if (scene != nullptr)
		{
			changeState(scene->Update(delta));
		}
	}

	void Render()
	{
		if (scene != nullptr)
			scene->Render();
	}


} &GameStateManager = Singleton<class GameStateManager>::instanceRef;