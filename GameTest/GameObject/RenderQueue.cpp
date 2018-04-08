#include "stdafx.h"

#include <algorithm>
#include "RenderQueue.h"
#include "GameObject.h"
#include "../Particle/Emitter.h"
#include "../App/SimpleLogger.h"

template<typename T>
bool RenderQueue::checkDuplicate(T* object)
{
	// Empty
	return false;
}

template<>
bool RenderQueue::checkDuplicate(GameObject* object)
{
	return (std::find(m_gameobjects.begin(), m_gameobjects.end(), object) != m_gameobjects.end());
}
template<>
bool RenderQueue::checkDuplicate(Emitter* object)
{
	return (std::find(m_emitters.begin(), m_emitters.end(), object) != m_emitters.end());
}

template<typename T>
RenderQueue& RenderQueue::add(T* object)
{
	SimpleLogger.ErrorStatic("Attempting to add object of unknown type");
	// Do nothing
	return *this;
}
template<>
RenderQueue& RenderQueue::add(GameObject* object)
{
	if (checkDuplicate<GameObject>(object))
		return *this;

	m_gameobjects.push_back(object);
	m_totalObjects++;
	return *this;
}
template<>
RenderQueue& RenderQueue::add(Emitter* object)
{
	if (checkDuplicate<Emitter>(object))
		return *this;

	m_emitters.push_back(object);
	m_totalEmitters++;
	return *this;
}

template<typename T>
RenderQueue& RenderQueue::remove(T* object)
{
	SimpleLogger.ErrorStatic("Attempting to remove object of unknown type");
	return *this;
}
template<>
RenderQueue& RenderQueue::remove(GameObject* object)
{
	Utility::EraseVectorByValue(m_gameobjects, object);
	m_totalObjects = (u_int)m_gameobjects.size();
	return *this;
}
template<>
RenderQueue& RenderQueue::remove(Emitter* object)
{
	Utility::EraseVectorByValue(m_emitters, object);
	m_totalEmitters = (u_int)m_emitters.size();
	return *this;
}

void RenderQueue::initAll()
{
	for (u_int i = 0; i < m_totalObjects; i++)
	{
		m_gameobjects[i]->Init();
	}

	// Emitter Init
}

void RenderQueue::updateAll(float delta)
{
	for (u_int i = 0; i < m_totalObjects; i++)
	{
		m_gameobjects[i]->Update(delta);
	}

	for (u_int i = 0; i < m_totalEmitters; i++)
	{
		m_emitters[i]->Update();
	}
}

void RenderQueue::drawAll()
{
	for (u_int i = 0; i < m_totalObjects; i++)
	{
		m_gameobjects[i]->Draw();
	}

	for (u_int i = 0; i < m_totalEmitters; i++)
	{
		m_emitters[i]->Draw();
	}
}

void RenderQueue::clear()
{
	m_gameobjects.clear();
	m_emitters.clear();
	m_totalObjects = 0;
	m_totalEmitters = 0;
}