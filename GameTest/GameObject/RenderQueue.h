
#pragma once

#include "../Utility/Singleton.h"

#include <Windows.h>
#include <vector>
#include <algorithm>

class RenderQueue
{
	friend class GameObject;
	friend class Emitter;
private:
	// Objects to draw
	std::vector<GameObject*> m_gameobjects;
	u_int					 m_totalObjects = 0;

	std::vector<Emitter*>	m_emitters;
	u_int					m_totalEmitters = 0;
public:
	template<typename T>
	bool checkDuplicate(T* object);

	template<typename T>
	RenderQueue& add(T* object);

	template<typename T>
	RenderQueue& remove(T* object);

	// Init Objects
	void initAll();
	// Update Objects
	void updateAll(float delta);
	// Draw Objects
	void drawAll();


};