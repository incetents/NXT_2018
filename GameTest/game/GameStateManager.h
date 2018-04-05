#pragma once

#include "../Utility/Singleton.h"

static class GameStateManager : public Singleton<class GameStateManager>
{
private:

public:
	enum class States
	{
		NONE = -1,
		MENU = 0,
		GAMEPLAY = 1
	};
	struct GlobalData
	{
		float test;
	};
	States		m_currentState;
	
	// Function Pointers
	void (GameStateManager::*RenderFunction)(void) = &GameStateManager::UpdateNull;

	void UpdateNull()
	{

	}
	void UpdateMenu()
	{

	}

public:
	GlobalData	m_data;

	const States& getState() const
	{
		return m_currentState;
	}
	void changeState(States state)
	{
		m_currentState = state;

		switch (m_currentState)
		{

		}
	}

	void Init() {}
	void Update() {}


} &GameStateManager = Singleton<class GameStateManager>::instanceRef;;