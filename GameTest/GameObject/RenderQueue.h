
#pragma once

#include "../Utility/Singleton.h"

#include <Windows.h>
#include <vector>
#include <algorithm>

static class _RenderQueue : Singleton<class _RenderQueue>
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
	_RenderQueue& add(T* object);

	template<typename T>
	_RenderQueue& remove(T* object);

	// Draw Objects
	void			drawAll();


} &RenderQueue = Singleton<class _RenderQueue>::instanceRef;